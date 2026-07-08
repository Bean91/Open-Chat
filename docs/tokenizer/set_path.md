```cpp
void set_path(std::filesystem::path path)
```
---
## Basic Info
Sets the path to vocab.
### Return Type
Returns `void`
### Parameters
| Parameter | Type                    | Use      | Optional |
|-----------|-------------------------|----------|----------|
| `path`    | `std::filesystem::path` | New path | ❌       |

---
## Example

```cpp
// Calling the set_path() function
tokenizer t("bestvocab.txt");
t.set_path("nah-im-a-better-vocab.txt");
```