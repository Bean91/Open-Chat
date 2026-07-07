## Overloads
```cpp
void changeOne(char mat, size_t row, size_t col, float d)
```
### Parameters
| Parameter | Type     | Use                        | Optional |
|-----------|----------|----------------------------|----------|
| `mat`     | `char`   | Specifies attention matrix | ❌       |
| `row`     | `size_t` | Specifies row in matrix    | ❌       |
| `col`     | `size_t` | Specifies column in matrix | ❌       |
| `d`       | `float`  | Specifies change to value  | ❌       |
---
```cpp
void changeOne(size_t layer, float d, size_t n_in, size_t n_out)
```
### Parameters
| Parameter | Type     | Use                                  | Optional |
|-----------|----------|--------------------------------------|----------|
| `layer`   | `size_t` | Specifies layer                      | ❌       |
| `n_in`    | `size_t` | Specifies start connection of weight | ❌       |
| `n_out`   | `size_t` | Specifies end connection of weight   | ❌       |
| `d`       | `float`  | Specifies change to value            | ❌       |
---
```cpp
void changeOne(size_t layer, float d, size_t n_in)
```
### Parameters
| Parameter | Type     | Use                       | Optional |
|-----------|----------|---------------------------|----------|
| `layer`   | `size_t` | Specifies layer           | ❌       |
| `n_in`    | `size_t` | Specifies bias neuron     | ❌       |
| `d`       | `float`  | Specifies change to value | ❌       |
---
## Basic Info
Changes one individual parameter of the model

---
## Example

```cpp
// Calling the changeOne() function
block b({128, 512, 128}, 128);
b.changeOne("q", 12, 103, 0.01465);
```