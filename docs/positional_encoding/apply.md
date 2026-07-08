```cpp
utility::matrix apply()
```
---
## Basic Info
Applies positional encodings onto the held matrix.
### Return Type
Returns a [`utility::matrix`]("../utility/matrix.md")

---
## Example

```cpp
// Calling the apply() function
utility::matrix x;
positionalEncoding p(x);
x = p.apply();
```