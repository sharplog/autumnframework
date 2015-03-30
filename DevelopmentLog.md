## 07/26/2007 ##
  * add const to some class member functions
  * ported to VS2005, AIX5L, Ubuntu6.06, Solaris10

## 07/22/2007 ##
  * Wrapper files can be auto-generated before compile with VC
  * using std::string-like things in public header file, not using using directives of namespace std.

## 07/21/2007 ##
  * fixed Issues1-3
  * add namespace Autumn for Autumn framework.

## 07/20/2007 ##
Autumn framework and AutumnGen support multi-inheritance, including direct and indirect inheritance. Indirect inheritance should list base classes in doccomment.

## 07/04/2007 ##
AutumnGen support multi-inheritance, but only for multiple father classes, not for multiple father's father classes.

## 05/21/2007 ##
  * ported and tested on AIX5L.
  * release ver 0.4.0.

## 05/18/2007 ##
  * has ported to solaris and ubuntu.
  * fix a bug: can't judge return type like "classXXX `*`" correctly.
  * add makefile for AutumnGen.
  * use CC to generate dependency.
  * Wrapper file is generated when compiling, not included in source package.

## 05/17/2007 ##
AutumnGen has been passed tests with Autumn framework on windows.

## 05/12/2007 ##
  * AutumnGen has been written and passed some simple tests. It doesn't support local bean now.
  * Autumn framework and its schema have some according changement also. Schema support init-method, destroy-method and delete-method(this method is for some bean like singletons ).

## 04/27/2007 ##
  * change "type" to "bean", remove "type" element in configure file.
  * optimize creating and deleting customized type bean.
  * **begin to write AutumnGen code.**

## 04/16/2007 ##
Move the defination of instance factory method from product's wrapper into factory's wrapper. That is more resonable because those methods are factory's.

## 04/05/2007 ##
Complete writing simple chinese user guide.

## 03/30/2007 ##
Compile and test with VC++ 2005.

## 03/22/2007 ##
  * erase bean's attributes: initializable and destroyable. bean supports init and destroy function however, it's decided by definition of bean wrapper.
  * optimize TypeManager object.

## 03/21/2007 ##
  * constuctor argument and property's type needn't be set in config file both, are got with wrapper.
  * bean support factory-method attibute.
  * erase name attribute from argument element.
  * tested on VC6.

## 03/18/2007 ##
  * unite IBasicType and ICombinedType into IAutumnType.
  * simplize TypeManager.
  * judge which type a value is by type bean, not TypeManager.
  * don't support property setter overloading.
  * support bean ref
  * type needn't be set in config file, can be get with wrapper

## 03/16/2007 ##
change BeanFactoryImpl to be not a singleton.

## 03/13/2007 ##
  1. implement factory pattern:
    * instance factory: use "factory-bean" attribute of bean.
    * static factory method: one bean support only one factory method.
  1. refine makefile to generate object file list and dependence file.
  1. test ver 0.2.0 on aix, ubuntu and solaris.
  1. release ver 0.2.0.

## 03/12/2007 ##
implement instance factory pattern. Tested on VC6. I used a simple way to get it: pass factory instance to bean wrapper->createBean as a constructor argument, and define it as a argument also. I will add 

&lt;factory-bean&gt;

 tag in schema.

## 03/06/2007 ##

fix three bugs:
  * don't close dynamic libraries when exiting progress.
  * don't free TypeManager when free BeanFactory.
  * a dead loop in TypeManager->isCustomized() function.

## 03/05/2007 ##
  * release 0.1.0 version.