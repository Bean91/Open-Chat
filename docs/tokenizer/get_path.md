```cpp
std::filesystem::path get_path()
```
---
## Basic Info
Returns the path where vocab is saved.
### Return Type
Returns an `std::filesystem::path`

---
## Example

```cpp
// Calling the get_path() function
tokenizer t("hello.txt");
t.get_path();
```