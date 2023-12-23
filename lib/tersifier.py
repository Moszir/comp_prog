import pathlib


class BufferedWriter:
    def __init__(self, source, target):
        self.__source = source
        self.__target = target
        self.__buffer = ''

    _verbatim_prefixes = {'#', '//>'}

    def terse(self):
        self.__buffer = ''
        in_comment_block = False
        with self.__source.open() as source:
            with self.__target.open(encoding='utf-8', mode='w') as target:
                for line in source.readlines():
                    if in_comment_block:
                        if '*/' in line:
                            in_comment_block = False
                        continue
                    if '/*' in line:
                        in_comment_block = True
                        continue

                    if any((line.startswith(prefix) for prefix in self._verbatim_prefixes)):
                        if len(self.__buffer) > 0:
                            target.write(self.__buffer + '\n\n')
                            self.__buffer = ''
                        target.write(line)
                        continue

                    if '//' in line:
                        line = line[:line.index('//')]
                    self.__buffer += line.strip()
                    if len(self.__buffer) > 100:
                        i = self.__buffer.find(' ', 100)
                        if i != -1:
                            target.write(self.__buffer[:i])
                            target.write('\n')
                            self.__buffer = self.__buffer[(i+1):]
                if self.__buffer:
                    target.write(self.__buffer + '\n\n')


for file_path in pathlib.Path('.').rglob('*.hpp'):
    if not file_path.name.endswith('_terse.hpp'):
        new_path = file_path.parent / (file_path.name[:-4] + '_terse.hpp')
        BufferedWriter(source=file_path, target=new_path).terse()
