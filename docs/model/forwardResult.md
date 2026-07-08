```cpp
struct forwardResult {
    utility::matrix dist;
    utility::matrix unembed;
    utility::matrix lastHidden;
    size_t seq_len;
};
```
---
## Basic Info
This strutcture store data about the last hidden layer which is important for back propogation.
### Variables
| Variable     | Type                                      | Use                                  | Optional |
|--------------|-------------------------------------------|--------------------------------------|----------|
| `dist`       | [`utility::matrix`](../utility/matrix.md) | Distribution of tokens               | ❌        |
| `unembed`    | [`utility::matrix`](../utility/matrix.md) | Unembed matrix used                  | ❌        |
| `lastHidden` | [`utility::matrix`](../utility/matrix.md) | Matrix before scaled against unembed | ❌        |
| `seq_len`    | `size_t`                                  | Number of inputted tokens            | ❌        |
---
## Example
```cpp
// Using forwardResult structure
model m();
forwardResult result = m.forwardPassInternal({69, 69, 91, 42, 420});
```