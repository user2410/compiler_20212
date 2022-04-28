/* 
 * @copyright (c) 2008, Hedspi, Hanoi University of Technology
 * @author Huu-Duc Nguyen
 * @version 1.0
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symtab.h"

void freeObject(Object* obj);
void freeScope(Scope* scope);
void freeObjectList(ObjectNode *objList);
void freeReferenceList(ObjectNode *objList);

SymTab* symtab;
Type* intType;
Type* charType;

/******************* Type utilities ******************************/

Type* makeIntType(void) {
  Type* type = (Type*) malloc(sizeof(Type));
  type->typeClass = TP_INT;
  return type;
}

Type* makeCharType(void) {
  Type* type = (Type*) malloc(sizeof(Type));
  type->typeClass = TP_CHAR;
  return type;
}

Type* makeArrayType(int arraySize, Type* elementType) {
  Type* type = (Type*) malloc(sizeof(Type));
  type->typeClass = TP_ARRAY;
  type->arraySize = arraySize;
  type->elementType = elementType;
  return type;
}

Type* duplicateType(Type* type) {
	Type * t = (Type*) malloc(sizeof(Type));
	t-> typeClass = type->typeClass;
  if(t->typeClass == TP_ARRAY){
  	t->arraySize = type->arraySize;
  	t->elementType = duplicateType(type->elementType);
  }
  return t;
  // TODO
}

int compareType(Type* type1, Type* type2) {
  if (type1->typeClass == type2->typeClass) {
    if (type1->typeClass == TP_ARRAY) {
      if (type1->arraySize == type2->arraySize)
        return compareType(type1->elementType, type2->elementType);
      else return 0;
    } else return 1;
  } else return 0;
}

void freeType(Type* type) {
  if(type->typeClass == TP_ARRAY){
    freeType(type->elementType);
  }
  free(type);
}

/******************* Constant utility ******************************/

ConstantValue* makeIntConstant(int i) {
	ConstantValue *c = (ConstantValue*)malloc(sizeof(ConstantValue));
	c->type = TP_INT;
	c->intValue = i;
	return c;
  // TODO
}

ConstantValue* makeCharConstant(char ch) {
  ConstantValue *c = (ConstantValue*)malloc(sizeof(ConstantValue));
  c->type = TP_CHAR;
  c->charValue = ch;
  return c;
  // TODO
}

ConstantValue* duplicateConstantValue(ConstantValue* v) {
  ConstantValue* c = (ConstantValue*)malloc(sizeof(ConstantValue));
  memcpy(c, v, sizeof(ConstantValue));
  return c;
  // TODO
}

/******************* Object utilities ******************************/

Scope* createScope(Object* owner, Scope* outer) {
  Scope* scope = (Scope*) malloc(sizeof(Scope));
  scope->objList = NULL;
  scope->owner = owner;
  scope->outer = outer;
  return scope;
}

Object* createProgramObject(char *programName) {
  Object* program = (Object*) malloc(sizeof(Object));
  strcpy(program->name, programName);
  program->kind = OBJ_PROGRAM;
  program->progAttrs = (ProgramAttributes*) malloc(sizeof(ProgramAttributes));
  program->progAttrs->scope = createScope(program,NULL);
  symtab->program = program;

  return program;
}

Object* createConstantObject(char *name) {
  Object* constant = (Object*) malloc(sizeof(Object));
  strcpy(constant->name, name);
  constant->kind = OBJ_CONSTANT;
  
  constant->constAttrs = (ConstantAttributes*)malloc(sizeof(ConstantAttributes));
  
  return constant;
  // TODO - OK
}

Object* createTypeObject(char *name) {
  Object* obj = (Object*) malloc(sizeof(Object));
  strcpy(obj->name, name);
  obj->kind = OBJ_TYPE;

  obj->typeAttrs = (TypeAttributes*)malloc(sizeof(TypeAttributes));

  return obj;
  // TODO - OK
}

Object* createVariableObject(char *name) {
  Object* var = (Object*) malloc(sizeof(Object));
  strcpy(var->name, name);
  var->kind = OBJ_VARIABLE;

  var->varAttrs = (VariableAttributes*)malloc(sizeof(VariableAttributes));
  var->varAttrs->scope = symtab->currentScope;

  return var;
  // TODO - OK
}

Object* createFunctionObject(char *name) {
  Object* func = (Object*) malloc(sizeof(Object));
  strcpy(func->name, name);
  func->kind = OBJ_FUNCTION;

  func->funcAttrs = (FunctionAttributes*)malloc(sizeof(FunctionAttributes));
  func->funcAttrs->paramList = NULL;
  func->funcAttrs->scope = createScope(func, symtab->currentScope);

  return func;
  // TODO - OK
}

Object* createProcedureObject(char *name) {
  Object* proc = (Object*) malloc(sizeof(Object));
  strcpy(proc->name, name);
  proc->kind = OBJ_PROCEDURE;

  proc->procAttrs = (ProcedureAttributes*)malloc(sizeof(ProgramAttributes));
  proc->procAttrs->paramList = NULL;
  proc->procAttrs->scope = createScope(proc, symtab->currentScope);

  return proc;
  // TODO - OK
}

Object* createParameterObject(char *name, enum ParamKind kind, Object* owner) {
  Object* param = (Object*) malloc(sizeof(Object));
  strcpy(param->name, name);
  param->kind = OBJ_PARAMETER;

  param->paramAttrs = (ParameterAttributes*)malloc(sizeof(ProgramAttributes));
  param->paramAttrs->kind = kind;
  param->paramAttrs->function = owner;

  return param;
  // TODO - OK
}

void freeObject(Object* obj) {
  switch(obj->kind)
  {
    case OBJ_CONSTANT:
      free(obj->constAttrs->value);
      free(obj->constAttrs);
      break;
    case OBJ_VARIABLE:
      freeType(obj->varAttrs->type);
      free(obj->varAttrs);
      break;
    case OBJ_TYPE:
      freeType(obj->typeAttrs->actualType);
      free(obj->typeAttrs);
      break;
    case OBJ_FUNCTION:
      freeReferenceList(obj->funcAttrs->paramList);
      freeType(obj->funcAttrs->returnType);
      freeScope(obj->funcAttrs->scope);
      free(obj->funcAttrs);
      break;
    case OBJ_PROCEDURE:
      freeReferenceList(obj->procAttrs->paramList);
      freeScope(obj->procAttrs->scope);
      free(obj->progAttrs);
      break;
    case OBJ_PARAMETER:
      freeType(obj->paramAttrs->type);
      free(obj->paramAttrs);
      break;
    case OBJ_PROGRAM:
      freeScope(obj->progAttrs->scope);
      free(obj->progAttrs);
      break;
  }

  free(obj);
  // TODO
}

void freeScope(Scope* scope) {
  freeObjectList(scope->objList);
  free(scope);
  // TODO
}

void freeObjectList(ObjectNode *objList) {
  ObjectNode* node = objList;

  while(node)
  {
    objList = node;
    node = node->next;
    freeObject(objList->object);
    free(objList);
  }
}

void freeReferenceList(ObjectNode *objList) {
  ObjectNode* node = objList;

  while(node){
    objList = node;
    node = node->next;
    freeType(objList->object->paramAttrs->type);
    free(objList->object->paramAttrs);
    // free(objList->object);
    free(objList);
  }
  // TODO
}

void addObject(ObjectNode **objList, Object* obj) {
  ObjectNode* node = (ObjectNode*) malloc(sizeof(ObjectNode));
  node->object = obj;
  node->next = NULL;
  if ((*objList) == NULL) 
    *objList = node;
  else {
    ObjectNode *n = *objList;
    while (n->next != NULL) 
      n = n->next;
    n->next = node;
  }
}

Object* findObject(ObjectNode *objList, char *name) {
  ObjectNode* node = objList;

  while(node->next){
    if(strcmp(name, node->object->name) == 0)
      return node->object;
    node = node->next;
  }

  return NULL;
  // TODO
}

/******************* others ******************************/

void initSymTab(void) {
  Object* obj;
  Object* param;

  symtab = (SymTab*) malloc(sizeof(SymTab));
  symtab->globalObjectList = NULL;
  symtab->currentScope = NULL;
  symtab->program = NULL;
  
  obj = createFunctionObject("READC");
  obj->funcAttrs->returnType = makeCharType();
  addObject(&(symtab->globalObjectList), obj);

  obj = createFunctionObject("READI");
  obj->funcAttrs->returnType = makeIntType();
  addObject(&(symtab->globalObjectList), obj);

  obj = createProcedureObject("WRITEI");
  addObject(&(symtab->globalObjectList), obj);
  enterBlock(obj->procAttrs->scope);
  param = createParameterObject("i", PARAM_VALUE, obj);
  param->paramAttrs->type = makeIntType();
  declareObject(param);
  // addObject(&(obj->procAttrs->paramList),param);
  exitBlock();

  obj = createProcedureObject("WRITEC");
  addObject(&(symtab->globalObjectList), obj);
  enterBlock(obj->procAttrs->scope);
  param = createParameterObject("ch", PARAM_VALUE, obj);
  param->paramAttrs->type = makeCharType();
  declareObject(param);
  // addObject(&(obj->procAttrs->paramList),param);
  exitBlock();

  obj = createProcedureObject("WRITELN");
  addObject(&(symtab->globalObjectList), obj);

  intType = makeIntType();
  charType = makeCharType();
}

void cleanSymTab(void) {
  freeObject(symtab->program);
  freeObjectList(symtab->globalObjectList);
  free(symtab);
  freeType(intType);
  freeType(charType);
}

void enterBlock(Scope* scope) {
  symtab->currentScope = scope;
}

void exitBlock(void) {
  symtab->currentScope = symtab->currentScope->outer;
}

void declareObject(Object* obj) {
  if (obj->kind == OBJ_PARAMETER) {
    Object* owner = symtab->currentScope->owner;
    switch (owner->kind) {
    case OBJ_FUNCTION:
      addObject(&(owner->funcAttrs->paramList), obj);
      break;
    case OBJ_PROCEDURE:
      addObject(&(owner->procAttrs->paramList), obj);
      break;
    default:
      break;
    }
  }
 
  addObject(&(symtab->currentScope->objList), obj);
}


