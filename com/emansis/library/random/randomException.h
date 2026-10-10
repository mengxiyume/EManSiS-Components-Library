#pragma once
#include "../../identify_tables/idt_exception.h"
#include "../exception/baseException.h"
#include "./random.h"
#include "../define_emansis.h"

namespace emansis {
    namespace exception {
        namespace Random {
            /// @brief  随机数异常
            class Exception : public BaseException {
            private:
                /// @brief 异常种子
                const emansis::random::Random::InitSeed_Type m_nSeed;
                /// @brief  异常发出文件
                const char* m_szFilePath;
                /// @brief  异常发出行
                uint32_t    m_uLine;
                /// @brief  异常附带信息
                ExceptionMessageText_Type m_textParam;
            public:
                /// @brief              随机数异常类构造
                /// @param id           异常编号
                /// @param msg          异常信息
                /// @param seed         异常种子
                /// @param param        异常附带信息
                /// @param ptrFilePath  异常发出文件
                /// @param ptrLine      异常发出行
                Exception
                ( const ExceptionIdentify_Type&     id
                , const ExceptionMessageText_Type&  msg
                , const emansis::random::Random::InitSeed_Type& errSeed
                , const ExceptionMessageText_Type&  param
                , const char*                       ptrFilePath
                ,       uint32_t                    ptrLine) 
                : BaseException (id, msg)
                , m_nSeed       (errSeed)
                , m_textParam   (param)
                , m_szFilePath  (ptrFilePath)
                , m_uLine       (ptrLine) { }
                /// @brief      获取异常种子
                /// @return     异常种子
                const int64_t   getSeed () const noexcept { return m_nSeed; }
                /// @brief      获取异常发出文件
                /// @return     异常发出文件
                const char*     getPath () const noexcept { return m_szFilePath; }
                /// @brief      获取异常发出行
                /// @return     异常发出行
                const uint32_t  getLine () const noexcept { return m_uLine; }
                /// @brief      获取异常附带信息
                /// @return     异常附带信息
                const ExceptionMessageText_Type&    getParamText   () const noexcept { return m_textParam; }
                /// @brief      获取异常数据
                /// @return     格式化的异常数据串
                virtual ExceptionOutBuffer_Type what() const noexcept { 
                    std::stringstream ss;
                    ExceptionOutBuffer_Type 
                    buffer =    "PointerException:";
                    buffer +=   toText();
                    buffer +=   "seed=\'0x";
                    ss << std::hex << getSeed();
                    buffer +=   ss.str();
                    ss.str("");
                    ss.clear();
                    buffer +=   "\' On ";
                    buffer +=   getPath() == nullptr ? "error code is no such file" : getPath();
                    buffer +=   ":";
                    ss << std::dec << getLine();
                    buffer +=   ss.str();
                    ss.str("");
                    ss.clear();
                    buffer +=   " ";
                    buffer +=   getParamText();
                    return buffer;
                }
            };
            /// @brief          随机数异常-种子为0
            /// @param path     异常发生文件
            /// @param line     异常发生行
            /// @param param    额外信息
            class EmptySeedRandomException : public Exception { public: EmptySeedRandomException(const char* path, uint32_t line, const emansis::random::Random::InitSeed_Type seed, const ExceptionMessageText_Type& param = "") : Exception(IDE_EXCEPTION_RANDOM_SEED_OF_ZERO, "Random seed is 0", seed, param, path, line) {} };
        /// @brief              随机数空种子异常
        /// @param _SEED_       异常种子
        /// @param _PARAM_TEXT_ 额外信息
        #define RANDOM_SEED_OF_ZERO_EXCEPTION_EMANSIS(_SEED_, _PARAM_TEXT_) emansis::exception::Random::EmptySeedRandomException(__FILE__, __LINE__, ((emansis::random::Random::InitSeed_Type)_SEED_), (_PARAM_TEXT_))
            /// @brief          随机数异常-生成器
            /// @param path     异常发生文件
            /// @param line     异常发生行
            /// @param seed     异常种子
            /// @param param    额外信息
            class XorShiftRandomException : public Exception { public : XorShiftRandomException(ExceptionIdentify_Type errId, const char* path, uint32_t line, const emansis::random::Random::InitSeed_Type seed, const ExceptionMessageText_Type& param = "") : Exception(errId, "xor shift error", seed, param, path, line) {} };
        /// @brief              生成器异常-过大的移位量
        /// @param _SEED_       异常种子
        /// @param _MAXSIZE_    最大容许量
        /// @param _VAR_        给定的量
        #define RANDOM_SHIFT_VALUE_TOO_BIG_EXCEPTION_EMANSIS(_SEED_, _MAXSIZE_, _VAR_) emansis::exception::Random::XorShiftRandomException(IDE_EXCEPTION_RANDOM_OUT_OF_SHIFT_BIT, __FILE__, __LINE__, ((emansis::random::Random::InitSeed_Type)_SEED_), \
        std::string("Max shift size[")  += std::string(STR_INT8_VAR_EMANSIS(_MAXSIZE_)) += \
        std::string("] set")            += std::string(PATCH_VAR_NAME_EMANSIS(_VAR_))   += \
        std::string(":[")               += std::string(STR_INT8_VAR_EMANSIS(_VAR_))     )  
        
        /// @brief              生成器异常-类型宽度为0
        /// @param _TYPE_       异常类型
        #define RANDOM_ZERO_OF_LENGTH_EXCEPTION_EMANSIS(_TYPE_) emansis::exception::Random::XorShiftRandomException(IDE_EXCEPTION_RANDOM_ZERO_OF_SHIFT_WIDTH, __FILE__, __LINE__, NULL, "type[" PATCH_VAR_NAME_EMANSIS(_TYPE_) "]length is set zero")
        }
    }
}