```cpp
void set_vocab(std::vector<std::string> vocab)
```
---
## Basic Info
Sets the vocab.
### Return Type
Returns `void`
### Parameters
| Parameter | Type                       | Use       | Optional |
|-----------|----------------------------|-----------|----------|
| `token`   | `std::vector<std::string>` | New vocab | ❌       |

---
## Example

```cpp
// Calling the set_vocab() function
tokenizer t("bestvocab.txt");
t.set_vocab({"i'm", "a", "super", "short", "vocab", "list", "that", "sux"});
```