```cpp
struct matrix {
    size_t rows, cols;
    std::vector<float> data;

    matrix(size_t r, size_t c) : rows(r), cols(c), data(r * c, 0.0f) {}
    matrix(): rows(0), cols(0), data(0, 0.0f) {}

    float* operator[](size_t row_index) {
        return &data[row_index * cols];
    }

    const float* operator[](size_t row_index) const {
        return &data[row_index * cols];
    }
};
```
---
## Basic Info
This strutcture stores a matrix in a flattened 1D `std::vector<float>`.
### Variables
| Variable | Type                 | Use                | Optional |
|----------|----------------------|--------------------|----------|
| `rows`   | `size_t`             | Number of rows     | ❌        |
| `cols`   | `size_t`             | Number of columns  | ❌        |
| `data`   | `std::vector<float>` | Raw flattened data | ❌        |
---
## Example
```cpp
// Using matrix structure
utility::matrix a(42, 91);
a[39][69] = 0.42042042;
a[12][83] = a[28][75];
```