```cpp
void init()
```
---
## Basic Info
Initializes the neural network and attention matrices (called in a constructor normally).
### Return Type
Returns `void`

---
## Example

```cpp
// Calling the init() function
block b({128, 512, 128}, 128);
b.init();
```