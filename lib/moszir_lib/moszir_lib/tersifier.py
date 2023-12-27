import pathlib
import typing


class BufferedWriter:
    def __init__(self, source: pathlib.Path, target: pathlib.Path):
        self.__source = source
        self.__target = target
        self.__buffer = ''

    _verbatim_prefixes = {'#', '//>'}

    def __dump_buffer(
            self,
            target: typing.TextIO,
            end_index: typing.Optional[int] = None,
            ending: str = '\n') -> None:
        if len(self.__buffer) > 0:
            if end_index is not None and end_index > 0:
                target.write(self.__buffer[:end_index] + ending)
                self.__buffer = self.__buffer[end_index:]
            else:
                target.write(self.__buffer + ending)
                self.__buffer = ''

    def terse(self):
        """ Tersifies the source into the target

        Lines that contain /* or */, and those in between are completely ignored.
        Don't use /* and */ in lines that should not be ignored.

        Lines containing // have the part starting with it chopped off.
        """
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
                        self.__dump_buffer(target)
                        target.write(line)  # has '\n'
                        continue

                    if '//' in line:
                        line = line[:line.index('//')]
                    self.__buffer += line.strip()
                    if len(self.__buffer) > 100:
                        i = self.__buffer.find(' ', 100)
                        self.__dump_buffer(target, end_index=i)
                self.__dump_buffer(target, ending='\n\n')


print(pathlib.Path(__file__).parent)

for p in pathlib.Path(__file__).parent.iterdir():
    if p.is_dir():
        for file_path in p.rglob('*.hpp'):
            if not file_path.name.endswith('_terse.hpp'):
                new_path = file_path.parent / (file_path.name[:-4] + '_terse.hpp')
                BufferedWriter(source=file_path, target=new_path).terse()
