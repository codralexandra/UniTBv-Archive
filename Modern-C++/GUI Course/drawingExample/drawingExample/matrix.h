#ifndef MATRIX_H
#define MATRIX_H

#include <cassert>
#include <utility>
#include <vector>

template <class T>
class Matrix
{
public:
    using Position = std::pair<std::size_t, std::size_t>;

public:
    Matrix(std::size_t rows = 0, std::size_t cols = 0)
        : m_rows{ rows }
        , m_cols{ cols }
    {
        m_data.reserve(m_rows * m_cols);
    }

    Matrix(std::size_t rows, std::size_t cols, const T& val)
        : Matrix(rows, cols)
    {
        m_data.assign(m_data.capacity(), val);
    }

    std::size_t GetRows() const noexcept
    {
        return m_rows;
    }

    std::size_t GetCols() const noexcept
    {
        return m_cols;
    }

    const T& operator[] (const Position& position) const
    {
        const auto& [row, col] = position;
        const auto index = row * m_cols + col;
        assert(index < m_data.size());
        return m_data[index];
    }

    T& operator[] (const Position& position)
    {
        const auto& [row, col] = position;
        const auto index = row * m_cols + col;
        assert(index < m_data.size());
        return m_data[index];
    }

private:
    std::size_t m_rows;
    std::size_t m_cols;
    std::vector<T> m_data;
};

#endif // MATRIX_H
