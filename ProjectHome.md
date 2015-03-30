This project implements Dependency Injection for C++. It supports property setter injection and constructor injection. It is compiled on multiple platform. It supports POCO (Plain Old C++ Object) and has no constraints on the classes you create. It has no incursion to your program code.

Autumn framework contains two parts:
  * a dynamic library and
  * a wrapper generator named AutumnGen

Autumn use a _[Small, simple, cross-platform, free and fast C++ XML Parser](http://www.applied-mathematics.net/)_ written by Frank Vanden Berghen to parse config file.

## 07/26/2007 Ver 0.5.0 released. ##
This version:
  * support multi-inheritance, including direct and indirect inheritance. Indirect inheritance should list base classes in doccomment.
  * add namespace Autumn for Autumn framework.
  * decorate some class member functions with const.
  * other changes, including Issues 1~3

## 05/21/2007 Ver 0.4.0 released. ##
This version:
  * has **AutumnGen**, a generator for wrapper files. You needn't now write any code to use Autumn framework, you can generate wrapper files(a head file and a implementation file) from a head file with AutumnGen.
  * bean support init-method, destroy-method and delete-method attributes.
  * change "type" to "bean", remove "type" element in configure file.

## 03/26/2007 Ver 0.3.0 released. ##
This version:
  * needn't set property's type or constructor argument's type in configuration file. If set, it will replace the type got with wrapper.
  * bean supports factory-method attribute and multiple factory methods, and don't support overloading.
  * erase bean's attributes: initializable and destroyable. Bean supports init and destroy function however, it's decided by definition of bean wrapper
  * support bean reference.
  * unite IBasicType and ICombinedType into IAutumnType.

## 03/13/2007 Ver 0.2.0 released. ##
This version supports creating bean using 'instance factory' and 'static factory method' patterns. You can find samples in test project.


## 03/05/2007 Ver 0.1.0 released. ##
You can download source code [here](http://code.google.com/p/autumnframework/downloads/list). A simple install guide is [here](InstallGuide.md).The code has been compiled on:
  * WindowsXP with Visual C++ 6.0
  * Linux Ubuntu 6.06 with GCC 4.0.3
  * SunOS 5.10 i86pc with Sun C++ 5.8
  * AIX 5L with XL C V7.0


## 01/16/2007 Ver 0.1.0 beta for Windows VC6 released. ##
You can download it [here](http://code.google.com/p/autumnframework/downloads/list). Some docs are [here](AutumnManual.md). CppDoc is [here](http://autumnframework.googlecode.com/svn/trunk/doc/CppDoc/index.htm).

It may be very babyish now, because I don't know Spring well and do this to imitate Spring in a hurry. I will write some docs ASAP. Now, it support:
  1. Support property injection and constructor injection.Only two constructors now, one has arguments and one has no argument. The setter function name should be like setXXX where XXX is a property name. You may not obey that rule if you rewrite the file BeanWrapperMacro.h.
  1. Support following basic type: char, short, int, long, float, double, char`*`, string, and some docrated with unsigned.
  1. Support class injection. (A class is named as a bean in Autumn like in Spring.)
  1. Support customized type using interface IBasicType.
  1. Support pointer to above types.
  1. Support singleton.
  1. Support initialization and destroyation functions.
  1. Support property setter overloading.
  1. Supoort dependence(it may be not like Spring).
  1. Support multiple dynamic libraries and local library(bean is in main process).
  1. Support configuration of log file path and level.