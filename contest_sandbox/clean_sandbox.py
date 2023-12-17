""" Make the sandbox ready for another contest without losing the current one.

1. Copies the existing source and input files into an `archive_{j}` folder.
2. Copies `template.cpp` to all source files.
3. Clears the input files.
"""
import pathlib
import shutil

NUMBER_OF_FILES = 10

archive_folder = None
for folder_index in range(100):
    candidate = pathlib.Path(f'archive_{folder_index}')
    if not candidate.exists():
        archive_folder = candidate
        break

assert archive_folder is not None
archive_folder.mkdir()

template_string = open('template.cpp').read()

for i in range(NUMBER_OF_FILES):
    cpp_path = pathlib.Path(f'p_{i}.cpp')
    shutil.copy(cpp_path, archive_folder / cpp_path.name)
    with open(cpp_path, 'w') as cpp_file:
        cpp_file.write(template_string)

    input_path = pathlib.Path(f'p_{i}.txt')
    shutil.copy(input_path, archive_folder / input_path.name)
    with open(input_path, 'w') as input_file:
        input_file.write('\n')

