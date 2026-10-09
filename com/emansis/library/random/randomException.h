#pragma once
#include "../../identify_tables/idt_exception.h"
#include "../exception/baseException.h"

//FIXME: 改写异常处理

namespace emansis {
    namespace exception {
        namespace Random {
            /// @brief  随机数异常
            class Exception : public BaseException {
            private:
                /// @brief  异常指针
                const void* m_pErrPtr;
                /// @brief  异常发出文件
                const char* m_szFilePath;
                /// @brief  异常发出行
                uint32_t    m_uLine;
                /// @brief  异常附带信息
                ExceptionMessageText_Type m_textParam;
            public:
                /// @brief              指针异常类构造
                /// @param id           异常编号
                /// @param msg          异常信息
                /// @param errPtr       异常指针
                /// @param param        异常附带信息
                /// @param ptrFilePath  异常发出文件
                /// @param ptrLine      异常发出行
                Exception
                ( const ExceptionIdentify_Type&     id
                , const ExceptionMessageText_Type&  msg
                , void*                             errPtr
                , const ExceptionMessageText_Type&  param
                , const char*                       ptrFilePath
                ,       uint32_t                    ptrLine) 
                : BaseException (id, msg)
                , m_pErrPtr     (errPtr)
                , m_textParam   (param)
                , m_szFilePath  (ptrFilePath)
                , m_uLine       (ptrLine) { }
                /// @brief      获取异常指针
                /// @return     异常指针
                const void*     getPtr  () const noexcept { return m_pErrPtr; }
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
                    buffer +=   "errPtr=\'0x";
                    ss << std::hex << getPtr();
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
            /// @brief          空指针异常
            /// @param path     异常发生文件
            /// @param line     异常发生行
            /// @param param    额外信息
            class NullPointerException : public Exception { public: NullPointerException(const char* path, uint32_t line, const ExceptionMessageText_Type& param = "") : Exception(IDE_EXCEPTION_POINTER_NULLPOINTER, "This pointer is nullptr", nullptr, param, path, line) {} };
        }
    }
}