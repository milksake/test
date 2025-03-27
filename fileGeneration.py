import random
import string
import os

def generate_random_word(length=8):
    return ''.join(random.choices(string.ascii_lowercase, k=length))

def generate_large_file(file_name, file_size_in_gb, words_per_line=5):
    word_list = [generate_random_word() for _ in range(words_per_line)]
    line = ' '.join(word_list) + ' '
    bytes_per_line = len(line.encode('utf-8'))
    
    total_lines = (file_size_in_gb * 1024 * 1024 * 1024) // bytes_per_line
    with open(file_name, 'w') as file:
        for _ in range(total_lines):
            file.write(line)
    print(f"{file_name} complete")

file_size_in_gb = 20
num_files = 5
output_dir = './'

for i in range(num_files):
    file_name = os.path.join(output_dir, f"random_file_{i+1}.txt")
    generate_large_file(file_name, file_size_in_gb)
