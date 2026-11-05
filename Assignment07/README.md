# Assignment 07: Associative Arrays and Lempel-Ziv

For this assigmnet I built an associative array and used it as the dictionary for an LZ78 encoder.

`AssociativeArray.h` uses separate chaining so basically each bucket can hold multiple key/value pairs. I hash the key and use `%` to choose a bucket. When there are more entries than buckets, the table grows and moves each pair to its new bucket.

`LempelZiv.h` assigns the IDs to phrases as it reads the input. When it finds a new phrase, it writes the ID of the part it already knows, followed by the next character. It packs those bits into bytes and stores the padding count in the first byte.

## How to run this repo

From the `Assignment07` folder, run these:

```powershell
g++ -std=c++17 -Wall -Wextra tests.cpp -o tests.exe
.\tests.exe

g++ -std=c++17 -Wall -Wextra main.cpp -o main.exe
.\main.exe
```

The tests check essential things like inserting, looking up, updating, removing, and listing entries. They also check that entries survive a rehash and that the encoder produces the expected bytes for `abaaa`. All tests passed when I last ran it.

## Compression results

I used three inputs that were all 120 bytes so I could compare them directly. The encoded sizes include the byte that stores the padding count.

| Input | Original size | Encoded size | Space saved |
|---|---:|---:|---:|
| `a` repeated 120 times | 120 bytes | 22 bytes | 81.7% |
| `hello ` repeated 20 times | 120 bytes | 52 bytes | 56.7% |
| Big League Ballers sentence | 120 bytes | 108 bytes | 10.0% |

The repeated `a` compressed the most because the encoder could reuse longer and longer runs of the same letter. Repeating `hello ` also gave it a lot of phrases to reuse. The basketball sentence had more variety, so there were fewer chances to reuse phrases and it only saved 12 bytes. So after doing all of this I wander if there is a different type of encoder that would be better for just standarad sentences where most words and phrases are random.