TEMPLATE = subdirs

CONFIG+=ordered

SUBDIRS = \
    PayloadErbessdLib \
    Test

Test.depends = PayloadErbessdLib


