## Constructors
```cpp
model(class tokenizer &tokenizer, class embedder &embedder, std::vector<class block> &blocks, float learning_rate = 0.01)
```
Tokes the tokenizer, embedder, and blocks (as well as learning rate) as parameters and re-initializes them all.

```cpp
model(class tokenizer &tokenizer, std::pair<std::filesystem::path, std::vector<std::pair<std::pair<std::filesystem::path, std::vector<std::filesystem::path>>, std::filesystem::path>>> inputFiles)
```
Reads saved model from the inputed filepaths, takes tokenizer as parameter.

---
## Basic Info
A wrapper class that holds the entire model.

### Instance Variables
| Variable        | Type                                      |
|-----------------|-------------------------------------------|
| `tokenizer`     | [`tokenizer`](../tokenizer/tokenizer.md)  |
| `embedder`      | [`embedder`](../embedder/embedder.md)     |
| `blocks`        | [`std::vector<block>`](../block/block.md) |
| `learning_rate` | `float`                                   |
---
## Functions
 - [`changeLearningRate()`](./changeLearningRate.md)
 - [`decodeToken()`](./decodeToken.md)
 - [`forwardPass()`](./forwardPass.md)
 - [`forwardPassInternal()`](./forwardPassInternal.md)
 - [`init()`](./init.md)
 - [`saveToFile()`](./saveToFile.md)
 - [`tokenize()`](./tokenize.md)
 - [`train()`](./train.md)
---
## Example

```cpp
// Initializing a block
tokenizer tokenizer("vocab.txt");
embedder embedder("bestembedderever.bin");
std::vector<block> blocks = {{{128, 512, 128}, 128}};
model m(tokenizer, embedder, blocks);
```