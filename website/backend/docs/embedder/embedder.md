## Constructors
```cpp
embedder(size_t n_tok, size_t n_embd)
```
Initializes a new embedding table with `n_tok` tokens and `n_embd` dimensions.

```cpp
embedder(std::filesystem::path input)
```
Reads a saved embedding table.

---
## Basic Info
An embedder that converts a token ID into a long vector of floats.

### Instance Variables
| Variable    | Type                                        |
|-------------|---------------------------------------------|
| `table`     | [`utility::matrix`]("../utility/matrix.md") |
| `n_tok`     | `size_t`                                    |
| `n_embd`    | `size_t`                                    |
| `toks`      | `std::forward_list<int>`                    |
| `generator` | `std::default_random_engine`                |
| `initDist`  | `std::normal_distribution<float>`           |
---
## Functions
 - [`backward()`]("./backward.md")
 - [`changeOne()`]("./changeOne.md")
 - [`embed()`]("./embed.md")
 - [`getNEmbed()`]("./getNEmbed.md")
 - [`getTable()`]("./getTable.md")
 - [`init()`]("./init.md")
 - [`readFromFile()`]("./readFromFile.md")
 - [`saveToFile()`]("./saveToFile.md")
---
## Example

```cpp
// Initializing an embedder
embedder e("./embedder.bin");
```