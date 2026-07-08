```cpp
forwardResult forwardPassInternal(std::forward_list<int> tokens)
```
---
## Basic Info
Runs a full forward pass on the tokenized input. It returns the probability distribution for the next token, in addition to more metadata about the last hidden layeer.
### Return Type
Returns a [`forwardResult`](./forwardResult.md)
### Parameters
| Parameter | Type                     | Use           | Optional |
|-----------|--------------------------|---------------|----------|
| `tokens`  | `std::forward_list<int>` | List of Token | ❌        |

---
## Example

```cpp
// Calling the forwardPass() function
model m();
forwardResult out = m.forwardInternalPass({91, 42});
```