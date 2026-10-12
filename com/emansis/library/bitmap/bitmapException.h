#pragma once
#include "../../identify_tables/idt_exception.h"
#include "../exception/baseException.h"

namespace emansis {
    namespace exception {
        namespace BitMap {
            /// @brief  指针异常
            class Exception : public BaseException {
            private:
                /// @brief  异常发出文件
                const char* m_szFilePath;
                /// @brief  异常发出行
                uint32_t    m_uLine;
                /// @brief  异常附带信息
                ExceptionMessageText_Type m_textParam;
            public:
                /// @brief              位图异常类构造
                /// @param id           异常编号
                /// @param msg          异常信息
                /// @param param        异常附带信息
                /// @param ptrFilePath  异常发出文件
                /// @param ptrLine      异常发出行
                Exception
                ( const ExceptionIdentify_Type&     id
                , const ExceptionMessageText_Type&  msg
                , const ExceptionMessageText_Type&  param
                , const char*                       ptrFilePath
                ,       uint32_t                    ptrLine)
                : BaseException (id, msg)
                , m_textParam   (param)
                , m_szFilePath  (ptrFilePath)
                , m_uLine       (ptrLine) { }
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
                    buffer +=   " On ";
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

            /// @brief              位图异常
            /// @param errId        异常ID
            /// @param errMessage   异常信息
            /// @param path         异常发生文件
            /// @param line         异常发生行
            /// @param param        额外信息
            class BitMapException : public Exception { public: BitMapException(ExceptionIdentify_Type errId, const char* errMessage, const char* path, uint32_t line, const ExceptionMessageText_Type& param = "") : Exception(errId, errMessage, param, path, line) {} };
        /// @brief              位图异常-位图索引越界
        /// @param              异常索引值
        /// @param              最大索引值
        #define BITMAP_OUT_OF_RANGE_BITMAP_EXCEPTION_EMANSIS(_CUR_INDEX_, _MAX_INDEX_) emansis::exception::BitMap::BitMapException(IDE_EXCEPTION_BITMAP_OUT_OF_RANGE, "index is out of range", __FILE__, __LINE__, \
            std::string("\'")                           + STR_INT64_VAR_EMANSIS(_CUR_INDEX_) + \
            std::string("\' is out of max index \'")    + STR_INT64_VAR_EMANSIS(_MAX_INDEX_) + \
            std::string("\'")   )
        }
    }
}