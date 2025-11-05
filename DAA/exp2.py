import heapq

# Node structure for Huffman Tree
class Node:
    def __init__(self, char, freq):
        self.char = char
        self.freq = freq
        self.left = None
        self.right = None

    # comparator for priority queue (needed for heapq)
    def __lt__(self, other):
        return self.freq < other.freq


# Step 1: Build frequency dictionary
def build_frequency(text):
    freq = {}
    for char in text:
        freq[char] = freq.get(char, 0) + 1
    return freq


# Step 2: Build Huffman Tree
def build_huffman_tree(freq_dict):
    heap = [Node(ch, freq) for ch, freq in freq_dict.items()]
    heapq.heapify(heap)

    while len(heap) > 1:
        left = heapq.heappop(heap)
        right = heapq.heappop(heap)

        new_node = Node(None, left.freq + right.freq)
        new_node.left = left
        new_node.right = right
        heapq.heappush(heap, new_node)

    return heap[0]


# Step 3: Generate Huffman Codes (recursively traverse the tree)
def generate_codes(root, current_code="", codes=None):
    if codes is None:
        codes = {}

    if root is None:
        return codes

    if root.char is not None:
        codes[root.char] = current_code
        return codes

    generate_codes(root.left, current_code + "0", codes)
    generate_codes(root.right, current_code + "1", codes)
    return codes


# Step 4: Encode text
def huffman_encode(text):
    if not text:
        return {}, ""
    freq_dict = build_frequency(text)
    root = build_huffman_tree(freq_dict)
    codes = generate_codes(root)
    encoded_text = ''.join([codes[ch] for ch in text])
    return codes, encoded_text


# -------------------- Main Execution --------------------
if __name__ == "__main__":
    text = input("Enter the text to encode: ")

    codes, encoded_text = huffman_encode(text)

    print("\nCharacter Codes:")
    for ch in sorted(codes):  # sort for clean output
        print(f"{ch!r} : {codes[ch]}")

    print(f"\nEncoded Output: {encoded_text}")
