#pragma once

#include "../Header Files/NoCopy.h"

#include <elements.hpp>

class TableCellComposer : private NoCopy
{
public:
    using composer_fn = std::function<cycfi::elements::element_ptr(const std::string& str, size_t line, size_t index)>;

    TableCellComposer(const std::vector<std::vector<std::string>>& data, uint64_t lines, uint64_t columns, composer_fn&& fn)
        : m_Data(data), m_NumOfLines(lines), m_NumOfCols(columns), m_Composer(fn)
    {
        
    }

    cycfi::elements::element_ptr Compose(uint64_t line, uint64_t col)
    {
        return m_Composer(m_Data[line][col], line, col);
    }

    uint64_t Lines() { return m_NumOfLines; }
    uint64_t Columns() { return m_NumOfCols; }

private:
    std::vector<std::vector<std::string>> m_Data;
    uint64_t m_NumOfLines, m_NumOfCols;
    composer_fn m_Composer;
};

class TableList : public cycfi::elements::vlist, private NoCopy
{
public:
    using table_composer_ptr = std::shared_ptr<TableCellComposer>;

    cycfi::elements::element_ptr LineMaker(uint64_t line)
    {
        if (m_hList[line].get() == nullptr)
        {
            auto h_composer =
                cycfi::elements::basic_hcell_composer(m_TableComposer->Columns(),
                    [&, line](size_t col) 
                    {
                        return m_TableComposer->Compose(line, col); 
                    }
            );

            m_hList[line] = cycfi::elements::share(cycfi::elements::hlist(h_composer));
        }
        return m_hList[line];
    };

    TableList(table_composer_ptr ptr)
        : cycfi::elements::vlist(cycfi::elements::basic_vcell_composer(ptr->Lines(), [&](size_t line) {return LineMaker(line); })),
          m_TableComposer(ptr), m_hList(ptr->Lines(), nullptr)
    {

    }

protected:
    table_composer_ptr m_TableComposer;
    std::vector<cycfi::elements::element_ptr> m_hList;
};