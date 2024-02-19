TEMPLATE = subdirs

CONFIG+=ordered

SUBDIRS = \
    MQTTCommLib \
    Test




Test.depends = MQTTCommLib

