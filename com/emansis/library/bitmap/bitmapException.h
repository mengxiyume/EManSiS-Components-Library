#pragma once
#include "../../identify_tables/idt_exception.h"
#include "../exception/baseException.h"

namespace emansis {
    namespace exception {
        namespace BitMap {
            /// @brief  指针异常
            class Exception : public BaseException {
            private:
                /// @brief  异常变量
                const char* m_szValue;
                /// @brief  异常索引值
                const size_t m_uIndex;
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
                /// @param valueName    异常指针
                /// @param index        异常索引值
                /// @param param        异常附带信息
                /// @param ptrFilePath  异常发出文件
                /// @param ptrLine      异常发出行
                Exception
                ( const ExceptionIdentify_Type&     id
                , const ExceptionMessageText_Type&  msg
                , const char*                       valueName
                , const size_t                      index
                , const ExceptionMessageText_Type&  param
                , const char*                       ptrFilePath
                ,       uint32_t                    ptrLine) 
                : BaseException (id, msg)
                , m_szValue     (valueName)
                , m_uIndex      (index)
                , m_textParam   (param)
                , m_szFilePath  (ptrFilePath)
                , m_uLine       (ptrLine) { }
                /// @brief      获取异常变量
                /// @return     异常变量名
                const char*     getValName  () const noexcept { return m_szValue; }
                /// @brief      获取异常索引值
                /// @return     异常索引值
                const size_t    getIndex    () const noexcept { return m_uIndex; }
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
                    buffer =    "BitmapException:";
                    buffer +=   toText();
                    buffer +=   "\'_";
                    buffer +=   getValName();
                    buffer +=   "[";
                    ss     <<   std::dec << getIndex();
                    buffer +=   ss.str();
                    ss.str("");
                    ss.clear();
                    buffer +=   "]_\' On ";
                    buffer +=   getPath() == nullptr ? "error code is no such file" : getPath();
                    buffer +=   ":";
                    ss     <<   std::dec << getLine();
                    buffer +=   ss.str();
                    ss.str("");
                    ss.clear();
                    buffer +=   " ";
                    buffer +=   getParamText();
                    return buffer;
                }
            };
            /// @brief              位图索引越界异常
            /// @param path         异常发生文件
            /// @param line         异常发生行
            /// @param valueName    异常变量名
            /// @param index        异常索引值
            /// @param param        额外信息
            class OutOfRangeBitMapException : public Exception { public: OutOfRangeBitMapException(const char* path, uint32_t line, const char* valueName, const size_t index, const ExceptionMessageText_Type& param = "-1") : Exception(IDE_EXCEPTION_BITMAP_OUT_OF_RANGE, "Bitmap index is out of range", valueName, index, param, path, line) {} };
        /// @brief              位图索引越界异常宏定义
        /// @param _VAR_        异常量
        /// @param _PARAM_TEXT_ 额外信息
        #define OUT_OF_RANGE_BITMAP_EXCEPTION_EMANSIS(_VAR_, _PARAM_TEXT_) emansis::exception::BitMap::OutOfRangeBitMapException(__FILE__, __LINE__, (#_VAR_), (_VAR_), (_PARAM_TEXT_))
        }
    }
}