```cpp
std::vector<std::string>* get_vocab()
```
---
## Basic Info
Returns a pointer to the vocab vector.
### Return Type
Returns an `std::vector<std::string>*`

---
## Example

```cpp
// Calling the get_vocab() function
tokenizer t("hello.txt");
t.get_vocab();
```