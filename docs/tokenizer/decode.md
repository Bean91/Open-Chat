```cpp
std::string decode(std::forward_list<int> tokens)
```
---
## Basic Info
Decodes a token list.
### Return Type
Returns an `std::string`
### Parameters
| Parameter | Type                     | Use        | Optional |
|-----------|--------------------------|------------|----------|
| `tokens`  | `std::forward_list<int>` | Token list | ❌       |

---
## Example

```cpp
// Calling the decode() function
tokenizer t("bestvocab.txt");
std::cout << t.decode({91, 103, 4364, 1730});
```