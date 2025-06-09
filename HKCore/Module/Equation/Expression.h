// Expression -- 表达式解析库.
//

#ifndef _Expression_H_
#define _Expression_H_

#include <vector>
#include <string>
#include <map>
#include "boost/function.hpp"
#include "boost/bind.hpp"
#include "boost/smart_ptr.hpp"
#include "boost/spirit.hpp"
#include "boost/spirit/phoenix.hpp"
#include "boost/spirit/actor.hpp"

// IOperator操作保证线程安全
// 解析过程不能保证
namespace Expression
{
	///////////////////////////////////////////////////////////////////////////
	//
	//  alpha_parser class
	//
	///////////////////////////////////////////////////////////////////////////
	struct alpha_parser_ex : public boost::spirit::char_parser<alpha_parser_ex>
	{
		typedef alpha_parser_ex self_t;

		alpha_parser_ex() {}

		template <typename CharT>
		bool test(CharT ch) const
		{
			return ( (boost::spirit::impl::isalpha_(ch)) || (ch == '_') );
		}
	};

	alpha_parser_ex const alpha_p_ex = alpha_parser_ex();

	// CVariable
	struct CVariable
	{
		std::string Name;

		CVariable(){}
		CVariable(const std::string& n):Name(n){}

		// Name string包装，可控制是否大小写敏感
		bool operator==(const CVariable& oth) const
		{
			return Name == oth.Name;
		}

		bool operator<(const CVariable& oth) const
		{
			return Name < oth.Name;
		}

		// 部分string接口
		size_t length() const
		{
			return Name.length();
		}

		const char* c_str() const
		{
			return Name.c_str();
		}
	};

	// CVariableList
	typedef std::vector<CVariable> vecVar;
	struct CVariableList : public vecVar
	{
		CVariableList(){}

		CVariableList(const CVariable *pvars, size_t nCount)
			:vecVar( pvars, pvars+nCount ){}

		CVariableList& operator=(const CVariableList &oth)
		{
			assign(oth.begin(), oth.end());
			return *this;
		}

		void merge(const CVariableList &oth)
		{
			if(oth.empty()) return;
			for(const_iterator itr = oth.begin(), itr_end = oth.end();
				itr != itr_end; ++itr)
			{
				if(indexof(*itr) < 0)
				{
					push_back(*itr);
				}
			}
		}

		int indexof(const CVariable &value) const
		{
			const_iterator itrBegin = begin(), itrEnd = end();
			const_iterator itr = std::find(itrBegin, itrEnd, value);
			return (itr==itrEnd) ? -1 : int(std::distance(itrBegin,itr));
		}
	};

	// IOperator
	struct IOperator
	{
		virtual double Op(const double *) const = 0;         // 可重入,线程安全
		virtual const CVariableList& GetVariables() const = 0;
		virtual ~IOperator(){;}
	};
	
	typedef boost::shared_ptr<IOperator> IOperatorPtr;
	typedef std::map<CVariable, IOperatorPtr> COptrVarMap;

	// COpInVarlist
	struct COpInVarlist        // 根据pOp参数相对varlist的位置抽取出数据算出pOp的值
	{
		COpInVarlist(IOperatorPtr pOp, const CVariableList &varlist)     // varlist已经包含所有变量
			:m_pOp(pOp),m_dValue(0),m_IsSeriate(true)
		{
			if(!pOp) return;

			const CVariableList& opvarlist = pOp->GetVariables();

			if(opvarlist.empty())
			{
				m_dValue = pOp->Op(NULL);                 //直接取值
				m_pOp.reset();
			}
			else
			{
				m_Offset.resize( opvarlist.size() );
				std::transform(opvarlist.begin(), opvarlist.end(),
					m_Offset.begin(), 
					boost::bind(&CVariableList::indexof, varlist, _1)
				);

				// 是否连续
				for(std::vector<size_t>::const_iterator itr=m_Offset.begin()+1;//m_Offset不为空
					itr!=m_Offset.end(); ++itr)
				{
					if(*itr!=*(itr-1)+1)
					{
						m_IsSeriate = false;
						break;
					}
				}
			}
		}

		double GetValue(const double *Values) const
		{
			if(!m_pOp) //直接输出值
				return m_dValue;
			else if(m_IsSeriate) //如果连续，直接定位新位置
				return m_pOp->Op( Values + m_Offset[0]);
			else // 重组
			{
				size_t nCount = m_Offset.size();
				double *pvalue = (double*)alloca(sizeof(double)* nCount);     // 根据偏移得到数据列表

				for(size_t i=0; i<nCount; i++) pvalue[i] = Values[m_Offset[i]];

				return m_pOp->Op(pvalue);
			}
		}
		
		double GetDirectValue(const double *Values) const
		{
			return m_pOp? m_pOp->Op(Values) : m_dValue;
		}

		bool Included() const
		{
			return std::find(m_Offset.begin(), m_Offset.end(), -1) == m_Offset.end();
		}

	private:
		COpInVarlist(const COpInVarlist&);
		COpInVarlist& operator=(const COpInVarlist&);
			IOperatorPtr m_pOp;
			double m_dValue;
			std::vector<size_t> m_Offset;  // m_pOp的变量组对应varlist的位置
			bool m_IsSeriate;
	};

	// COpValue, 直接数据
	struct COpValue : IOperator
	{   
		COpValue(double Value) : m_dValue(Value) { }
		virtual double Op(const double *) const { return m_dValue;}
		virtual const CVariableList& GetVariables() const {return m_varlistEmpty;}

	protected:
		CVariableList m_varlistEmpty;
		double m_dValue;
	};

	// COpVar, 直接变量
	struct COpVar : IOperator
	{
		COpVar(std::string szItem)
		{
			CVariable var;
			var.Name = szItem;
			m_varlist.push_back( var );
		}

		virtual double Op(const double *value) const{ return *value; }
		virtual const CVariableList& GetVariables() const { return m_varlist; }

	protected:
		CVariableList m_varlist;
	};
	
	// 组合操作，接管生命周期
	// 单操作，如函数、正负号
	struct COpSingleBase : IOperator
	{
		COpSingleBase(IOperatorPtr val):m_val(val)	{}

		virtual const CVariableList& GetVariables() const
		{
			return m_val->GetVariables(); 
		}

	protected:
		IOperatorPtr m_val;
	};

	// COpBinary, 双操作，如加减乘除
	struct COpBinaryBase : IOperator
	{
		COpBinaryBase(IOperatorPtr A,IOperatorPtr B)
		{
		  //取得A，B的所有参数
			m_varlist = A->GetVariables();
			m_varlist.merge(B->GetVariables());
		  //缓存A与B所用参数相对于参数列表的位置
			m_pAIn = new COpInVarlist(A, m_varlist);
			m_pBIn = new COpInVarlist(B, m_varlist);
		}

		virtual const CVariableList& GetVariables() const
		{
			return m_varlist;
		}

		virtual ~COpBinaryBase()
		{
			delete m_pAIn;
			delete m_pBIn;
		}

	protected:
		COpInVarlist *m_pAIn;
		COpInVarlist *m_pBIn;
		CVariableList m_varlist;

	private:
		COpBinaryBase(const COpBinaryBase&);
		COpBinaryBase& operator=(const COpBinaryBase&);
	};

	// 单操作实现
	// 负号
	struct COpNegative : COpSingleBase
	{
		COpNegative(IOperatorPtr val) : COpSingleBase(val){}

		virtual double Op(const double *values) const
		{
			return -m_val->Op(values);
		}

	private:
		char m_sign;
	};

	// 双操作实现
	struct COpAdd : COpBinaryBase
	{        // A + B
		COpAdd(IOperatorPtr A, IOperatorPtr B):COpBinaryBase(A,B) {}
		virtual double Op(const double *values) const
		{
			return m_pAIn->GetDirectValue(values) + m_pBIn->GetValue(values);
		}
	};

	struct COpSubtract : COpBinaryBase
	{        // A - B
		COpSubtract(IOperatorPtr A, IOperatorPtr B):COpBinaryBase(A,B){}
		virtual double Op(const double *values) const
		{
			return m_pAIn->GetDirectValue(values) - m_pBIn->GetValue(values);
		}
	};

	struct COpMultiply : COpBinaryBase
	{        // A * B
		COpMultiply(IOperatorPtr A, IOperatorPtr B):COpBinaryBase(A,B){}
		virtual double Op(const double *values) const
		{
			return m_pAIn->GetDirectValue(values) * m_pBIn->GetValue(values);
		}
	};

	struct COpDivide : COpBinaryBase
	{        // A / B
		COpDivide(IOperatorPtr A, IOperatorPtr B) :COpBinaryBase(A,B) { }
		virtual double Op(const double *values) const
		{
			return m_pAIn->GetDirectValue(values) / m_pBIn->GetValue(values);
		}
	};

	struct COpPower : COpBinaryBase
	{        // A ^ B
		COpPower(IOperatorPtr A, IOperatorPtr B) :COpBinaryBase(A,B) { }
		virtual double Op(const double *values) const
		{
			double x = m_pAIn->GetDirectValue(values);
			double y = m_pBIn->GetValue(values);
			return pow(x,y);
		}
	};

	struct calc_closure : boost::spirit::closure<calc_closure, IOperatorPtr>
	{
		member1 val;
	};
	
	struct func_closure : boost::spirit::closure<func_closure, IOperatorPtr, CVariable>
	{
		member1 val;
		member2 name;
	};

	struct create_OpSign_impl
	{
		template <typename ParamA, typename ParamB>	//输入参数类型
        struct result
		{
            typedef IOperatorPtr type;	//返回类型
        };

        template <typename ParamA, typename ParamB>
        IOperatorPtr operator()(ParamA & start, ParamB & op) const
        {
			return (*start=='-')? IOperatorPtr(new COpNegative(op)) : op ;
        }
	};

	struct create_OpValue_impl
	{
		template <typename ParamA>	//输入参数类型
        struct result
		{
            typedef IOperatorPtr type;	//返回类型
        };

        template <typename ParamA>
        IOperatorPtr operator()(ParamA & val) const
        {
			return IOperatorPtr(new COpValue(val));
        }
	};

	//变量，可替换已知变量
	struct create_OpVar_impl
	{
		template <typename ParamA, typename ParamB>	//输入参数类型
        struct result
		{
            typedef IOperatorPtr type;	//返回类型
        };

        template <typename ParamA, typename ParamB>
        IOperatorPtr operator()(ParamA & start, ParamB & end) const
        {
			std::string varName(start, end);
			COptrVarMap::const_iterator itr = m_VarMap.find(varName);
			if(itr != m_VarMap.end())
				return itr->second;
			else
				return IOperatorPtr(new COpVar( varName ));
        }

		create_OpVar_impl(const COptrVarMap &VarMap):m_VarMap(VarMap)
		{
		}

	private:
		const COptrVarMap &m_VarMap;
	};

	template<class COperatorT>
	struct create_OpBinary_impl
	{
		template <typename ParamA, typename ParamB>	//输入参数类型
        struct result
		{
            typedef IOperatorPtr type;	//返回类型
        };

        template <typename ParamA, typename ParamB>
        IOperatorPtr operator()(ParamA & op1, ParamB & op2) const
        {
			return IOperatorPtr(new COperatorT(op1,op2));
        }
	};
	
	template<class COperatorT>
	struct create_OpUnary_impl
	{
		template <typename ParamA>	//输入参数类型
        struct result
		{
            typedef IOperatorPtr type;	//返回类型
        };
        template <typename ParamA>
        IOperatorPtr operator()(ParamA & op1) const
        {
			return IOperatorPtr(new COperatorT(op1));
        }
	};

	// 单参数函数map(name,func)=> func_parser, create_OpUnaryFunc_impl
	typedef boost::function1<double,double> unary_func_type;
	typedef std::map<CVariable, unary_func_type> mapUnaryFunc;
	// 单参函数的IOperator实现
	struct COpUnaryFunc : COpSingleBase
	{
		COpUnaryFunc(IOperatorPtr val, unary_func_type func) : COpSingleBase(val),m_func(func){}
		virtual double Op(const double *values) const{ return m_func(m_val->Op(values)); }

	private:
		unary_func_type m_func;
	};

	// 单参函数的phoenix::function实现
	struct create_OpUnaryFunc_impl
	{
		template <typename ParamA, typename ParamB>	//输入参数类型
        struct result
		{
            typedef IOperatorPtr type;	//返回类型
        };

		template <typename ParamA, typename ParamB>
        IOperatorPtr operator()(ParamA & name, ParamB & op) const
        {
			mapUnaryFunc::const_iterator itr = m_FuncMap.find(name);

			if(itr==m_FuncMap.end())
				return op;
			else
				return IOperatorPtr(new COpUnaryFunc(op,itr->second));
        }

		create_OpUnaryFunc_impl(const mapUnaryFunc &FuncMap):m_FuncMap(FuncMap){}

	private:
		const mapUnaryFunc &m_FuncMap;
	};

	// 按map的key查找
    struct func_parser
    {
		typedef CVariable result_t;   //定义解析器结果类型
		//参数是:扫描器，结果；返回：解析了多长
        template <typename ScannerT> 
		std::ptrdiff_t operator()(ScannerT const& scan, result_t& result) const
        {
            if (scan.at_end())  return -1;

			for(mapUnaryFunc::const_iterator itr=m_FuncMap.begin();
				itr!=m_FuncMap.end(); ++itr)
			{
				size_t len = itr->first.length();

				if (0 == strncmp(scan.first, itr->first.c_str(), len))
				{
					result = itr->first;
					scan.first+=len;
					return len;
				}
			}

			return -1;
        }

		func_parser(const mapUnaryFunc &FuncMap):m_FuncMap(FuncMap){}

	private:
		const mapUnaryFunc &m_FuncMap;
    };

	//四则运算语法类，它也使用了closure的内容策略
    struct calculator : public boost::spirit::grammar<calculator, calc_closure::context_t>
    {
		const phoenix::function<create_OpValue_impl> create_OpValue;
		const phoenix::function<create_OpVar_impl> create_OpVar;
		const phoenix::function<create_OpSign_impl> create_OpSign;
		const phoenix::function<create_OpBinary_impl<COpAdd> > create_OpAdd;
		const phoenix::function<create_OpBinary_impl<COpSubtract> > create_OpSub;
		const phoenix::function<create_OpBinary_impl<COpDivide> > create_OpDiv;
		const phoenix::function<create_OpBinary_impl<COpMultiply> > create_OpMul;
		const phoenix::function<create_OpBinary_impl<COpPower> > create_OpPow;
		const phoenix::function<create_OpUnaryFunc_impl> create_OpUnaryFunc;
		boost::spirit::functor_parser<func_parser> func_parser_p;  //用functor_parser包装成解析器

		COptrVarMap m_VarMap;
		mapUnaryFunc m_FuncMap;

		calculator()
			:create_OpVar(create_OpVar_impl(m_VarMap)),
			create_OpUnaryFunc(create_OpUnaryFunc_impl(m_FuncMap)),
			func_parser_p(func_parser(m_FuncMap))
		{}

		void AddFunc(const std::string& funcname, unary_func_type func)
		{
			m_FuncMap[funcname] = func;
		}

    	//语法类重要成员:struct definition
        template <typename ScannerT>
        struct definition
        {
    		// factor, term, exp的rule类型，同例三(ScannerT模板在使用时决定)
    		typedef boost::spirit::rule<ScannerT, calc_closure::context_t> rule_type;
    		rule_type factor, term, exp, pow, signfac;
			
			boost::spirit::rule<ScannerT, func_closure::context_t> func;
    
    		// 启动rule，在这个例子中，它也是递归的最顶层，负责把exp的最终结果赋值给框架本身。
    		boost::spirit::rule<ScannerT> rlStart;
            const boost::spirit::rule<ScannerT>& start() const { return rlStart; }
    		
    		//definition的构造函数，self参数引用的是calculator类的实例
            definition(calculator const& self)
            {
				using namespace boost::spirit;
				using namespace phoenix;
				
// 				factor = ureal_p[factor.val = self.create_OpValue(arg1)] | //实数
// 					func[factor.val = arg1] | // 函数
// 					lexeme_d[(alpha_p_ex >> *(alnum_p))][ factor.val = self.create_OpVar(arg1, arg2) ] | //变量
// 					('(' >> exp[factor.val = arg1] >> ')'); // 括号

				func = ( self.func_parser_p[func.name = arg1] >> 
					'(' >> exp[func.val = arg1] >> ')')[func.val = self.create_OpUnaryFunc(func.name,func.val)];
		
				factor = ureal_p[factor.val = self.create_OpValue(arg1)] | //实数
					func[factor.val = arg1] | // 函数
					lexeme_d[(alpha_p >> *(alnum_p))][ factor.val = self.create_OpVar(arg1, arg2) ] | //变量
					('(' >> exp[factor.val = arg1] >> ')'); // 括号
				
				// 正负号
				signfac = (!(ch_p('+')|'-') >> factor[ signfac.val = arg1])[ signfac.val = self.create_OpSign(arg1, signfac.val) ];

				pow = signfac[pow.val = arg1] >> 
					*( '^' >> signfac[pow.val = self.create_OpPow(pow.val, arg1) ] );

				term   = pow[term.val = arg1] >> 
					*( ('*' >> pow[term.val = self.create_OpMul(term.val, arg1) ] ) | 
						('/' >> pow[term.val = self.create_OpDiv(term.val, arg1) ]) );
				exp    = term[exp.val = arg1] >> 
					*( ('+' >> term[exp.val = self.create_OpAdd(exp.val, arg1)]) | 
						('-' >> term[exp.val = self.create_OpSub(exp.val, arg1) ]) );

    			rlStart  = exp[self.val = arg1];
            }
        };// struct definition
    };// class calculator

	struct CEquation
	{
		calculator m_calc;

		const COptrVarMap& getVarMap() const
		{
			return m_calc.m_VarMap;
		}

		COptrVarMap& getVarMap()
		{
			return m_calc.m_VarMap;
		}

		// 加入函数
		void AddFunc(const std::string& funcname, unary_func_type func)
		{
			m_calc.AddFunc(funcname,func);
		}

		// 加入常量
		void AddConst(const std::string& name, double val)
		{
			getVarMap()[name] = create_OpValue_impl()(val);
		}
        
		// 字符串形式方程，字符串形式为“变量名 = 公式”
		bool AddEquation(const std::string& equ, size_t *lastpos=NULL) // 接受
		{
			using namespace boost::spirit;
			rule<phrase_scanner_t> rlEqu;
			std::string name;
			IOperatorPtr val;
			rlEqu = (lexeme_d[(alpha_p >> *(alnum_p))][assign_a(name)] >> '=' >> m_calc[assign_a(val)])
					[ insert_at_a(m_calc.m_VarMap,name,val) ];
			parse_info<> r = parse(equ.c_str(), rlEqu, space_p);
			if(lastpos) *lastpos = r.stop - equ.c_str();
			return r.full;
		}

		// 从运算字符串生成操作对象
		IOperatorPtr CreateOperator(const char *pszExp, const char **pLastPos = NULL)
		{
			using namespace boost::spirit;

			IOperatorPtr op;
			parse_info<> r = parse( pszExp , m_calc[ assign_a(op) ], space_p); 
			
			if(pLastPos!=NULL) *pLastPos = r.stop;
			if(!r.full) op.reset();

			return op;
		}
	};
};// namespace Expression

#endif

