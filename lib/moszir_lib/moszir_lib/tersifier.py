import pathlib
import typing


class BufferedWriter:
    def __init__(self, source: pathlib.Path, target: pathlib.Path):
        self.__source = source
        self.__target = target
        self.__buffer = ''

    _verbatim_prefixes = {'#', '//>'}

    def terse(self):
        """ Tersifies the source into the target

        Lines that contain /* or */, and those in between are completely ignored.
        Don't use /* and */ in lines that should not be ignored.

        Lines containing // have the part starting with it chopped off.
        """
        in_comment_block = False
        with self.__source.open() as source:
            with self.__target.open(encoding='utf-8', mode='w') as target:
                target.write(f'// region {self.__source.name[:-4]}\n')
                for line in source.readlines():
                    if in_comment_block:
                        if '*/' in line:
                            in_comment_block = False
                        continue
                    if '/*' in line:
                        in_comment_block = True
                        continue

                    if any((line.startswith(prefix) for prefix in self._verbatim_prefixes)):
                        target.write(line)
                        continue

                    if '//' in line:
                        line = line[:line.index('//')] + '\n'
                    if line.rstrip() != '':
                        target.write(line)
                target.write(f'// endregion {self.__source.name[:-4]}\n')


print(pathlib.Path(__file__).parent)

for p in pathlib.Path(__file__).parent.iterdir():
    if p.is_dir():
        for file_path in p.rglob('*.hpp'):
            if not file_path.name.endswith('_terse.hpp'):
                new_path = file_path.parent / (file_path.name[:-4] + '_terse.hpp')
                BufferedWriter(source=file_path, target=new_path).terse()
