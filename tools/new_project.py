#!/usr/bin/python3
import os
import shutil


#源根目录
src_root = os.getcwd()
if os.path.basename(src_root) == 'tools':
    src_root = os.path.dirname(src_root)

def listdir_odir(path):
    lst = os.listdir(path)
    return filter(lambda x:os.path.isdir(os.path.join(path, x)), lst)

class NewProject:
    def cdir(self):
        """
        retval: 0正常退出，-1需要再试，1错误
        """
        d = input('请输入工程目录:')
        absd = os.path.abspath(d)
        if os.path.samefile(os.path.commonpath([absd, src_root]), src_root):
            while True:
                s = input('目标文件夹在源目录下，是否继续 确认(y), 取消(n):')
                if s == 'y':
                    break
                elif s == 'n':
                    return 1
        elif not os.path.exists(d):
            os.mkdir(d)
        elif not os.path.isdir(d):
            print('目标存在但不是文件夹')
            return -1
        elif len(os.listdir(d)) != 0:
            while True:
                s = input('目标文件夹非空，是否继续 确认(y), 取消(n), 列出(l):')
                if s == 'y':
                    break
                elif s == 'n':
                    return 1
                elif s == 'l':
                    os.system(f'ls {d} --color=auto -CF')
        self.d = d
        return 0

    def cdir_loop(self):
        while True:
            r = self.cdir()
            if r >= 0:
                return r

    def lns_cp(self):
        def src_(*args):
            return os.path.join(src_root, *args)
        def dst_(*args):
            return os.path.join(dst_root, *args)

        dst_root = self.d
        lst = list(listdir_odir(src_root))
        removes = ['obj', 'User', 'tools']
        for r in removes:
            try:
                lst.remove(r)
            except Exception:
                pass
        os.mkdir(dst_('obj'))
        for fn in lst:
            os.symlink(src_(fn), dst_(fn))
            os.symlink(src_('obj', fn), dst_('obj', fn))
        os.symlink(src_('.ld'), dst_('.ld'))
        shutil.copytree(src_('User'), dst_('User'))
        shutil.copytree(src_('tools'), dst_('tools'))
        shutil.copyfile(src_('Makefile'), dst_('Makefile'))


if __name__ == '__main__':
    prj = NewProject()
    r = prj.cdir_loop()
    if r > 0:
        exit()
    prj.lns_cp()
