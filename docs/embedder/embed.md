```cpp
std::vector<float> embed(int tok)
```
---
## Basic Info
Returns the embedding vector of the corresponding token
### Return Type
Returns a `std::vector<float>`

### Parameters
| Parameter | Type  | Use      | Optional |
|-----------|-------|----------|----------|
| `tok`     | `int` | Token ID | ❌        |
---
## Example

```cpp
// Calling the embed() function
embedder e(42, 42);
e.embed(91);
```