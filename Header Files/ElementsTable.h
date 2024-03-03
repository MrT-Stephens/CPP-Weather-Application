#pragma once

#include "../Header Files/NoCopy.h"

#include <elements.hpp>

/// <summary>
/// Composes a table cell
/// Will compose a cell using the given function
/// Composes every cell in the table with the correct data.
/// </summary>
class TableCellComposer : private NoCopy
{
public:
    using composer_fn = std::function<cycfi::elements::element_ptr(const std::string& str, size_t line, size_t index)>;

    /// <summary>
    /// Initializes a new instance of the <see cref="TableCellComposer"/> class.
    /// </summary>
    /// <param name="data"> The table data. </param>
    /// <param name="lines"> The number of rows. </param>
    /// <param name="columns"> The number of columns. </param>
    /// <param name="fn"> The function to use to compose the cell. </param>
    TableCellComposer(const std::vector<std::vector<std::string>>& data, uint64_t lines, uint64_t columns, composer_fn&& fn)
        : m_Data(data), m_NumOfLines(lines), m_NumOfCols(columns), m_Composer(fn)
    {
        
    }

    /// <summary>
    /// Composes the cell at the given line and column.
    /// Will insert the data at the given line and column into the cell.
    /// </summary>
    /// <param name="line"> The current line. </param>
    /// <param name="col"> The current column. </param>
    /// <returns> A shared pointer to the composed cell. </returns>
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

/// <summary>
/// The list of cells in the table.
/// Will create a list of cells in the table.
/// </summary>
class TableList : public cycfi::elements::vlist, private NoCopy
{
public:
    using table_composer_ptr = std::shared_ptr<TableCellComposer>;

    /// <summary>
    /// Creates the horizontal list of cells for the given row.
    /// </summary>
    /// <param name="line"> The current line. </param>
    /// <returns> A shared pointer to the horizontal list of cells. </returns>
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

    /// <summary>
    /// Initializes a new instance of the <see cref="TableList"/> class.
    /// </summary>
    /// <param name="ptr"> Pointer to an instance of <see cref="TableCellComposer"/>. </param>
    TableList(table_composer_ptr ptr)
        : cycfi::elements::vlist(cycfi::elements::basic_vcell_composer(ptr->Lines(), [&](size_t line) {return LineMaker(line); })),
          m_TableComposer(ptr), m_hList(ptr->Lines(), nullptr)
    {

    }

protected:
    table_composer_ptr m_TableComposer;
    std::vector<cycfi::elements::element_ptr> m_hList;
};