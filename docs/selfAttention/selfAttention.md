## Constructors
```cpp
selfAttention(size_t n_embd)
```
Initializes a self attention block with three square weight matrices following the passed `n_embd` dimensions.

---
## Basic Info
Applies self attention.

### Instance Variables
| Variable    | Type                                      |
|-------------|-------------------------------------------|
| `wq`        | [`utility::matrix`](../utility/matrix.md) |
| `wk`        | [`utility::matrix`](../utility/matrix.md) |
| `wv`        | [`utility::matrix`](../utility/matrix.md) |
| `q`         | [`utility::matrix`](../utility/matrix.md) |
| `k`         | [`utility::matrix`](../utility/matrix.md) |
| `v`         | [`utility::matrix`](../utility/matrix.md) |
| `p`         | [`utility::matrix`](../utility/matrix.md) |
| `x`         | [`utility::matrix`](../utility/matrix.md) |
| `n_tok`     | `size_t`                                  |
| `n_embd`    | `size_t`                                  |
| `generator` | `std::default_random_engine`              |
| `initDist`  | `std::normal_distribution<float>`         |
---
## Functions
 - [`attention()`](./attention.md)
 - [`backward()`](./backward.md)
 - [`changeOne()`](./changeOne.md)
 - [`getNEmbed()`](./getNEmbed.md)
 - [`readFromFile()`](./readFromFile.md)
 - [`saveToFile()`](./saveToFile.md)
---
## Example

```cpp
// Initializing a self attention block
selfAttention a(91);
```