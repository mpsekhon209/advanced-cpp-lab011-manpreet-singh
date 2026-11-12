# Map Analysis Laboratory

## Core goal
Students must implement a dictionary-like `Map` structure that stores key-value pairs and supports lookup, insertion, deletion, and updates.

## Required operations
Students must implement the following behavior:

- insert a new key-value pair;
- reject duplicate keys;
- find whether a key exists;
- update an existing value;
- remove an existing key;
- retrieve a value by key;
- list keys and values;
- maintain sorted order if appropriate for the design.

## Analysis expectations
Students should discuss:

- average-case time complexity of insertion, lookup, and deletion;
- best-case and worst-case behavior;
- why duplicate-key handling matters;
- the difference between a search by key and scanning all entries;
- trade-offs between sorted vectors and hash-based maps;
- memory overhead and performance of `keys()` and `values()`.

## Big-O focus
Students should explain the Big-O of:

- `insert`
- `contains`
- `update`
- `erase`
- `at`
- `keys`
- `values`

The expected design is a clear, well-explained mapping abstraction that makes trade-offs explicit.

## Chosen design: sorted vector
`Map` stores key-value pairs in a `std::vector` ordered by key. Insertion uses binary search to find the position, rejects an existing key, and inserts at that position. Lookup also uses binary search. Keeping the vector sorted makes key listing deterministic and allows `isSorted()` to verify the invariant.

For `n` entries, the operation costs are:

| Operation | Best case | Worst case | Reason |
| --- | --- | --- | --- |
| `insert` | O(log n) | O(n) | Binary search locates the position; vector elements may need to shift, and growth may reallocate. |
| `contains` | O(1) | O(log n) | Binary search can find the middle entry immediately or narrow the search logarithmically. |
| `update` | O(1) | O(log n) | Binary search locates the key; changing its integer value is O(1). |
| `erase` | O(1) | O(n) | Binary search can locate the key immediately; vector elements after the removed entry may shift left. |
| `at` | O(1) | O(log n) | Binary search locates the key; a missing key throws `std::out_of_range`. |
| `keys` | O(n) | O(n) | Each stored key is copied into the returned vector. |
| `values` | O(n) | O(n) | Each stored value is copied into the returned vector. |

The map uses O(n) storage, plus vector capacity and the stored strings. `keys()` and `values()` each allocate O(n) additional storage for their result. A hash table could offer average-case O(1) lookup, but it requires bucket storage, has no natural sorted order, and may degrade to O(n) lookup in the worst case. The sorted vector is a compact, straightforward choice for this lab, with fast lookup and deterministic traversal at the cost of linear-time insertion and deletion in the worst case.
