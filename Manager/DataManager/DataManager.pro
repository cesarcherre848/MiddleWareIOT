TEMPLATE = subdirs

CONFIG+=ordered

SUBDIRS = \
    DataManagerLib \
    Test


Test.depends = DataManagerLib

