#include "../../../library/atom/atom"
#include "../../../library/bitmap/bitmap"
#include <iostream>
#include <cstdint>
#include <utility>
#include <cstdlib>
#include <ctime>

namespace emansis {
    namespace example {
        namespace atom {
            /// @brief 继承计算原子基类
            class SimpleAtomExample : public emansis::atom::Atom {
            public:
                /// @brief  初始化设置传递函数
                SimpleAtomExample() : Atom(initProc_1, computProc_1) { }
            
                /// @brief 继承纯虚函数go
                virtual void go () {
                    //进行一些运行前操作
                    setConter_stopper(3);
                    //调用goRun进行运算
                    goRun();
                    //进行运算后操作
                }
                
                /// @brief  继承纯虚函数停止器
                /// @return 通过中继函数实现停止判断逻辑
                virtual state_stopper stopper() { return stopper(conter_stopper); }
            private:

                /// @brief          停止器
                /// @param conter   计数器的引用
                /// @return         应该停止时返回Atom::state_stopper::state_stop，否则返回Atom::state_stopper::state_continue
                state_stopper stopper(int& conter) { return --conter_stopper <= 0 ? state_stop : state_continue; }
            
                /// @brief          初始化停止计数器
                /// @param n        计数次数
                void setConter_stopper(int n) { conter_stopper = n; }
                //初始处理函数
                Proc initProc_1 = [](Precision_Type&& cache)->void const { cache = 8.0; };
            
                //计算函数
                Proc computProc_1 = [](Precision_Type&& cache)->void const { cache *= (1 - 0.5); };

                /// @brief 停止计算计数器 
                int conter_stopper = 0;
            };

            class Family : public emansis::atom::Atom {
            public:
                enum Gender {
                    Male    = 0,
                    Femal   = 1
                };
                virtual state_stopper stopper() { 
                    double probability = (double)rand() / (double)RAND_MAX;
                    if (m_uMaleCount != 0 && probability <= cache()) return state_stop;
                    return m_uMaleCount >= 1 ? state_stop : state_continue; }
                virtual void go() {
                    initializer(const_cast<Proc&>(initProc));
                    computation(const_cast<Proc&>(computProc));
                    //TODO:将额外处理函数作为Proc成员变量传入afterProc
                    goRun();
                }
                Family() : Atom() { }
        	    /// @brief 			获取成员数量
        	    /// @param gender 	需获取成员数量的性别
        	    /// @return 		指定性别成员的数量
        	    const	uint8_t 	count				(Gender gender) const noexcept { return gender == Male ? m_uMaleCount : m_uFemalCount; }
                friend std::ostream& operator<<(std::ostream& out, Family& obj);
            private:
                uint8_t m_uMaleCount    = 0;
                uint8_t m_uFemalCount   = 0;
                void clearMember() {
                    m_uMaleCount    = 0;
                    m_uFemalCount   = 0;
                }
                const Proc initProc   = [this](Precision_Type&& cache)->void { clearMember(); cache = 1.0; };
                const Proc computProc = [this](Precision_Type&& cache)->void {
                    //单步随机生男生女
                    int baby = rand() % 2;
                    if      (baby == Male)  ++m_uMaleCount;
                    else if (baby == Femal) ++ m_uFemalCount;
                    if      (m_uMaleCount >= 1)
                        cache *= (1 - (0.4));
                    else
                        cache *= (1 - (0.1));
                };
            };
            std::ostream& operator<<(std::ostream& out, Family& obj) {
                return out
                    << "Male    Count:" << (uint32_t)obj.m_uMaleCount << '\n'
                    << "Femal   Count:" << (uint32_t)obj.m_uFemalCount << '\n';;
            }
        }
    }
}

void test01() {
    emansis::example::atom::SimpleAtomExample aExample;
    aExample.go();
    std::cout << aExample.cache() << std::endl;
}

void test02() {
    // throw NULL_POINTER_EXCEPTION_EMANSIS("Test null pointer exception");
    int subject = 325;
    throw OUT_OF_RANGE_BITMAP_EXCEPTION_EMANSIS(subject, "Test out of range exception");
    // emansis::example::atom::Family f1;
    // for (int i = 0; i < 30; ++i) {
    //     f1.go();
    //     std::cout << f1 << std::endl;
    // }
}

int main() {
    srand(time(nullptr));
    // test01();
    try {
    test02();
    }
    catch (emansis::exception::BaseException& e) {
        std::cout << e.what() << std::endl;
    }
    catch (std::exception& e) {
        std::cout << "std::exception:" << e.what() << std::endl;
    }
    catch (...) {
        std::cout << "Unknown exception" << std::endl;

    }
    return 0;
}