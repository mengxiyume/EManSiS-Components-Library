#pragma once
#include <string>
#include <sstream>
#include <cstdint>
#include "../../identify_tables/idt_exception.h"

namespace emansis {
    namespace exception{
        /// @brief  异常基类
        class BaseException {
        public:
            /// @brief  异常编号类型
            typedef int32_t     ExceptionIdentify_Type;
            /// @brief  异常消息信息类型
            typedef std::string ExceptionMessageText_Type;
            /// @brief  异常输出缓冲区类型
            typedef std::string ExceptionOutBuffer_Type;
        protected:
            /// @brief  异常编号
            ExceptionIdentify_Type      m_iIdentifyNumber = -1;
            /// @brief  异常信息
            ExceptionMessageText_Type   m_textMessage;
        public:
            /// @brief      异常基类构造
            /// @param id   异常编号
            /// @param msg  异常信息
            BaseException(const ExceptionIdentify_Type& id, const ExceptionMessageText_Type& msg) noexcept
            :m_iIdentifyNumber  (id)
            ,m_textMessage      (msg) {}
            /// @brief      获取异常编号
            /// @return     异常编号
            const   ExceptionIdentify_Type&     getId       () const noexcept { return m_iIdentifyNumber; }
            /// @brief      获取异常信息
            /// @return     异常信息
            const   ExceptionMessageText_Type&  getMessage  () const noexcept { return m_textMessage; }
            /// @brief      转换数据为文本形式
            /// @return     格式化基础信息文本
                    ExceptionOutBuffer_Type     toText      () const noexcept {
                std::stringstream ss;

                ExceptionOutBuffer_Type 
                buffer =    "|E_0x";
                ss << std::hex << getId();
                buffer +=   ss.str();
                ss.str("");
                ss.clear();
                buffer +=   "|\'";
                buffer +=   getMessage();
                buffer +=   "\'|";
                return buffer;
            }
            /// @brief      获取错误信息
            /// @return     错误信息
            virtual ExceptionOutBuffer_Type     what        () const noexcept {
                ExceptionOutBuffer_Type 
                buffer =    "Exception:";
                buffer +=   toText();
                return buffer;
            }
        };
        /// @brief  异常类简称
        typedef BaseException Exception;
        /// @brief  定义未知异常
        class UnknownException : public BaseException { public: UnknownException() : BaseException(IDE_UNKNOWN_EXCEPTION, "unknown exception") { } };
    }
}