## Constructors
```cpp
tokenizer(std::filesystem::path path, bool input = false)
```
Reads saved vocab if `input` is `true` otherwise initializes new vocab.

---
## Basic Info
A tokenizer using a greedy algorithm.

### Instance Variables
| Variable | Type                       |
|----------|----------------------------|
| `vocab`  | `std::vector<std::string>` |
| `path`   | `std::filesystem::path`    |
---
## Functions
 - [`add_token()`](./add_token.md)
 - [`decode()`](./decode.md)
 - [`encode()`](./encode.md)
 - [`get_path()`](./get_path.md)
 - [`get_vocab()`](./get_vocab.md)
 - [`save_tokens()`](./save_tokens.md)
 - [`set_path()`](./set_path.md)
 - [`set_vocab()`](./set_vocab.md)
---
## Example

```cpp
// Initializing a tokenizer
tokenizer t("./tokenstokenstokensssss.txt");
```