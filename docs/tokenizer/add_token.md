```cpp
void add_token(std::string token)
```
---
## Basic Info
Adds a token to the vocab.
### Return Type
Returns `void`
### Parameters
| Parameter | Type          | Use       | Optional |
|-----------|---------------|-----------|----------|
| `token`   | `std::string` | New Token | ❌       |

---
## Example

```cpp
// Calling the add_token() function
tokenizer t("bestvocab.txt");
t.add_token("CoolNewToken !!! yay");
```