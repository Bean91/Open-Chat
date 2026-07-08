```cpp
std::forward_list<int> encode(std::string text)
```
---
## Basic Info
Encodes a string into a token list.
### Return Type
Returns an `std::string`
### Parameters
| Parameter | Type          | Use  | Optional |
|-----------|---------------|------|----------|
| `text`    | `std::string` | Text | ❌       |

---
## Example

```cpp
// Calling the encode() function
tokenizer t("bestvocab.txt");
std::cout << t.encode("Zephyr is a cute dog");
```