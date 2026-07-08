## Constructors
```cpp
positionalEncoding(utility::matrix x)
```
Initializes a positional encoding table based on the input matrix.

---
## Basic Info
Applies positional encodings.

### Instance Variables
| Variable | Type                                      |
|----------|-------------------------------------------|
| `n_embd` | `size_t`                                  |
| `n_in`   | `size_t`                                  |
| `table`  | [`utility::matrix`](../utility/matrix.md) |
| `x`      | [`utility::matrix`](../utility/matrix.md) |
---
## Functions
 - [`apply()`](./apply.md)
---
## Example

```cpp
// Initializing a positional encoding
utility::matrix x;
positionalEncoding p(x);
```