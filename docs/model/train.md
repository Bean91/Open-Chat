```cpp
void train(std::string input, size_t epochs = 100)
```
---
## Basic Info
Trains the model.
### Return Type
Returns `void`
### Parameters
| Parameter | Type          | Use    | Optional |
|-----------|---------------|--------|----------|
| `input`   | `std::string` | Corpus | ❌       |
| `epochs`  | `size_t`      | Epochs | ✅       |

---
## Example

```cpp
// Calling the train() function
model m();
m.train("Hello, World! My name is Billy Bob Joe and I like cheese!", 12);
```