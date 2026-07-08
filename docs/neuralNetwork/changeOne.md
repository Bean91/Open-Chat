## Overloads
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
Changes one individual parameter of the network

---
## Example

```cpp
// Calling the changeOne() function
neuralNetwork n({128, 512, 128});
n.changeOne(2, 12, 103, 0.01465);
```