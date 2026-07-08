## Overloads
```cpp
void changeOne(float d, size_t n_in)
```
### Parameters
| Parameter | Type     | Use                       | Optional |
|-----------|----------|---------------------------|----------|
| `n_in`    | `size_t` | Specifies bias neuron     | ❌       |
| `d`       | `float`  | Specifies change to value | ❌       |
---
```cpp
void changeOne(float d, size_t n_in, size_t n_out)
```
### Parameters
| Parameter | Type     | Use                                  | Optional |
|-----------|----------|--------------------------------------|----------|
| `n_in`    | `size_t` | Specifies start connection of weight | ❌       |
| `n_out`   | `size_t` | Specifies end connection of weight   | ❌       |
| `d`       | `float`  | Specifies change to value            | ❌       |
---
## Basic Info
Changes one individual parameter of the layer

---
## Example
```cpp
// Calling the changeOne() function
layer l(512, 128);
l.changeOne("q", 12, 103, 0.01465);
```