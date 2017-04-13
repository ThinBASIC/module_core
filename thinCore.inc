  #IF NOT %DEF(%TRUE)
    %TRUE  = 1
  #ENDIF
  #IF NOT %DEF(%FALSE)
    %FALSE = 0
  #ENDIF

  '------------------------------------------------------------------------------
  'Global declares
  '------------------------------------------------------------------------------
  %thinBasic_ForceOverWrite         =  1&   'Used in thinBasic_LoadSymbol to force symbol over writing

  %VarMainType_IsNumber             = 20&
  %VarMainType_IsString             = 30&
  %VarMainType_IsAsciiZ             = 25&
  %VarMainType_IsVariant            = 50&

  %VarSubType_Byte                  =  1&
  %VarSubType_Integer               =  2&
  %VarSubType_Word                  =  3&
  %VarSubType_DWord                 =  4&
  %VarSubType_Long                  =  5&
  %VarSubType_Quad                  =  6&
  %VarSubType_Single                =  7&
  %VarSubType_Double                =  8&
  %VarSubType_Currency              =  9&
  %VarSubType_Ext                   = 10&
  %VarSubType_Variant               = 50&


  '------------------------------------------------------------------------------
  'Return Types from functions/Subs
  '------------------------------------------------------------------------------
  %thinBasic_ReturnNone             =  0&   'Used in thinBasic_LoadSymbol to define a sub
  %thinBasic_ReturnCodeNone         = %thinBasic_ReturnNone

  %thinBasic_ReturnNumber           = 20&   'Used in thinBasic_LoadSymbol to define a function returning a EXT number
  %thinBasic_ReturnCodeNumber       = %thinBasic_ReturnNumber

  %thinBasic_ReturnString           = 30&   'Used in thinBasic_LoadSymbol to define a function returning a string
  %thinBasic_ReturnCodeString       = %thinBasic_ReturnString

  %thinBasic_ReturnCodeByte         =  1&
  %thinBasic_ReturnCodeInteger      =  2&
  %thinBasic_ReturnCodeWord         =  3&
  %thinBasic_ReturnCodeDWord        =  4&
  %thinBasic_ReturnCodeLong         =  5&
  %thinBasic_ReturnCodeQuad         =  6&
  %thinBasic_ReturnCodeSingle       =  7&
  %thinBasic_ReturnCodeDouble       =  8&
  %thinBasic_ReturnCodeCurrency     =  9&
  %thinBasic_ReturnCodeExt          = 10&
  '------------------------------------------------------------------------------

  %thinBasic_BufferType_IsFile      = 0&
  %thinBasic_BufferType_IsScript    = 1&

  %thinBasic_CallingProgram_GUI     = 1&
  %thinBasic_CallingProgram_Console = 2&


  '----------------------------------------------------------------------------
  'thinBasic_Init / thinBasic_Run / thinBasic_Release
  '----------------------------------------------------------------------------
  ' Description
  '   the 3 functions to call in sequence in order to execute a script
  '   when using thinCore.dll (thinBasic engine) as embedded scripting language
  '
  '
  '----------------------------------------------------------------------------
  DECLARE FUNCTION  thinBasic_Init                                _
                          LIB "thinCore.dll"                      _
                          ALIAS "thinBasic_Init"                  _
                          (                                       _
                            BYVAL hWnd            AS LONG       , _
                            BYVAL cInstance       AS LONG       , _
                            BYVAL sKey            AS STRING       _
                          ) AS LONG

  DECLARE FUNCTION  thinBasic_Run                                 _
                          LIB "thinCore.dll"                      _
                          ALIAS "thinBasic_Run"                   _
                          (                                       _
                            BYVAL hScript         AS LONG       , _
                            BYVAL sBuffer         AS STRING     , _
                            BYVAL BufferType      AS LONG       , _
                  OPTIONAL  BYVAL Options         AS LONG       , _
                            BYVAL DebugMode       AS LONG       , _
                            BYVAL LogMode         AS LONG       , _
                            BYVAL ObfuscateMode   AS LONG       , _
                            BYVAL CallingProgram  AS LONG       , _
                            BYVAL DependancyMode  AS LONG         _
                          ) AS LONG

  DECLARE FUNCTION  thinBasic_Release                             _
                          LIB "thinCore.dll"                      _
                          ALIAS "thinBasic_Release"               _
                          (                                       _
                            BYVAL hScript         AS LONG         _
                          ) AS LONG


  '----------------------------------------------------------------------------
  'thinBasic_AddIncludePath
  '----------------------------------------------------------------------------
  ' Description
  '   when a file us specified in #INCLUDE withou a fully qualified path
  '   thinBasic will search for the file using script or executable path
  '   If not found, thinBasic will search in some directories specified by #INCLUDEDIR.
  '   This function is the equivalent of #INCLUDEDIR but executed from the aoutside
  '   of the script
  '
  ' Parameters
  '   sNewIncludeDir  : full path of the new include dir when thinBasic will serach fon files
  '                     specified in #INCLUDE
  '
  '   ReturnCode  : None
  '
  '   Call this function after thinBasic_Init but before thinBasic_Run
  '----------------------------------------------------------------------------
  DECLARE FUNCTION  thinBasic_AddIncludePath                      _
                          LIB "thinCore.dll"                      _
                          ALIAS "thinBasic_AddIncludePath"        _
                          (                                       _
                            BYVAL sNewIncludeDir  AS STRING       _
                          ) AS LONG

  '----------------------------------------------------------------------------
  'thinBasic_LoadSymbol
  '----------------------------------------------------------------------------
  ' Description
  '   Creates e new keyword inside interpreter.
  '   You define your own Function or Sub inside your program. Then call
  '   thinBasic_LoadSymbol to add a new keyword connected to your new function/sub
  '
  ' Parameters
  '   SymbolName  : Name you want to give to your sub or function inside the
  '                 interpreter. It is the new keyword name.
  '
  '   ReturnCode  : specify what kind of var your function returns
  '                 Use predefined constants:
  '                 %thinBasic_ReturnNumber
  '                 %thinBasic_ReturnString
  '                 %thinBasic_ReturnNone
  '                 If SymbolName will end with "$" char, ReturnCode will
  '                 be forced to %thinBasic_ReturnString
  '                 Note: if you pass a pointer to a SUB routine and ReturnCode
  '                       is different from %thinBasic_ReturnNone, a GPF will be
  '                       fired by the Operating System.
  '                 Note: if ReturnCode <= 0 then %thinBasic_ReturnNone will be
  '                       assumed
  '
  '   FunctionOrSubPointer:
  '                 DWORD returned by CODEPTR function pointing to the function
  '                 that will be called when SymbolName keyword will be encountered
  '                 during script execution
  '
  '   ForceOverWrite:
  '                 If different from 0 it means that even if SymbolName
  '                 already exists as a keyword, you want to overwrite it with
  '                 a new one.
  '                 For example, if you want to overwrite behave of MID$
  '                 creating your own MID$ function, set this parameter to a value
  '                 > 0 like in this example:
  '                 thinBasic_LoadSymbol("MID$", %thinBasic_ReturnString, CODEPTR(MyMid), 1)
  '
  ' Possible Return Code
  '   >0 = no error, return the associated SymbolName ID
  '   -1 = empty SymbolName
  '   -2 = duplicated SymbolName and no ForceOverWrite flag
  '   -3 = invalid sub/function pointer
  '   -4 = SymbolName contains invalid char(s)
  '
  ' Example
  '   thinBasic_LoadSymbol "MyNewFunction", %thinBasic_ReturnNumber, CODEPTR(MyFunc)
  '----------------------------------------------------------------------------
  DECLARE FUNCTION  thinBasic_LoadSymbol                            _
                          LIB "thinCore.DLL"                        _
                          ALIAS "thinBasic_LoadSymbol"              _
                          (                                         _
                            BYVAL SymbolName            AS STRING , _
                            BYVAL ReturnCode            AS LONG   , _
                            BYVAL FunctionOrSubPointer  AS DWORD  , _
                            OPTIONAL                                _
                            BYVAL ForceOverWrite        AS LONG     _
                          ) AS LONG

  '----------------------------------------------------------------------------
  'thinBasic_LoadSymbolEX
  '----------------------------------------------------------------------------
  ' Description
  '   Creates e new keyword inside interpreter.
  '   You define your own Function or Sub inside your program. Then call
  '   thinBasic_LoadSymbol to add a new keyword connected to your new function/sub
  '
  ' Parameters
  '   SymbolName  : Name you want to give to your sub or function inside the
  '                 interpreter. It is the new keyword name.
  '
  '   ReturnCode  : specify what kind of var your function returns
  '                 Use predefined constants:
  '                 %thinBasic_ReturnNumber
  '                 %thinBasic_ReturnString
  '                 %thinBasic_ReturnNone
  '                 If SymbolName will end with "$" char, ReturnCode will
  '                 be forced to %thinBasic_ReturnString
  '                 Note: if you pass a pointer to a SUB routine and ReturnCode
  '                       is different from %thinBasic_ReturnNone, a GPF will be
  '                       fired by the Operating System.
  '                 Note: if ReturnCode <= 0 then %thinBasic_ReturnNone will be
  '                       assumed
  '
  '   FunctionOrSubPointer:
  '                 DWORD returned by CODEPTR function pointing to the function
  '                 that will be called when SymbolName keyword will be encountered
  '                 during script execution
  '
  '   ForceOverWrite:
  '                 If different from 0 it means that even if SymbolName
  '                 already exists as a keyword, you want to overwrite it with
  '                 a new one.
  '                 For example, if you want to overwrite behave of MID$
  '                 creating your own MID$ function, set this parameter to a value
  '                 > 0 like in this example:
  '                 thinBasic_LoadSymbol("MID$", %thinBasic_ReturnString, CODEPTR(MyMid), 1)
  '   sSyntax:
  '                 Syntax of the symbol name
  '   sHelp:
  '                 help about the symbol name
  '
  ' Possible Return Code
  '   >0 = no error, return the associated SymbolName ID
  '   -1 = empty SymbolName
  '   -2 = duplicated SymbolName and no ForceOverWrite flag
  '   -3 = invalid sub/function pointer
  '   -4 = SymbolName contains invalid char(s)
  '
  ' Example
  '   thinBasic_LoadSymbol "MyNewFunction", %thinBasic_ReturnNumber, CODEPTR(MyFunc)
  '----------------------------------------------------------------------------
  DECLARE FUNCTION  thinBasic_LoadSymbolEX                          _
                          LIB "thinCore.DLL"                        _
                          ALIAS "thinBasic_LoadSymbolEX"            _
                          (                                         _
                            BYVAL SymbolName            AS STRING , _
                            BYVAL ReturnCode            AS LONG   , _
                            BYVAL FunctionOrSubPointer  AS DWORD  , _
                            OPTIONAL                                _
                            BYVAL ForceOverWrite        AS LONG   , _
                            BYVAL sSyntax               AS STRING , _
                            BYVAL sHelp                 AS STRING   _
                          ) AS LONG

  '----------------------------------------------------------------------------
  'thinBasic_VariableGetList
  '----------------------------------------------------------------------------
  ' Returns a string with the list of all variables of a specific stack level
  ' If StackLevel is missing, current stack level will be returned
  '----------------------------------------------------------------------------
  DECLARE FUNCTION thinBasic_VariableGetList                      _
                          LIB "thinCore.DLL"                      _
                          ALIAS "thinBasic_VariableGetList"       _
                          (                                       _
                            OPTIONAL                              _
                            BYVAL lStackLevel   AS LONG         , _
                            BYVAL sSep          AS STRING         _
                          ) AS STRING
  '----------------------------------------------------------------------------

  '----------------------------------------------------------------------------
  'thinBasic_VariableExists
  '----------------------------------------------------------------------------
  ' Returns true/false depending if the given name is a variable or not
  '----------------------------------------------------------------------------
  DECLARE FUNCTION  thinBasic_VariableExists                      _
                          LIB "thinCore.DLL"                      _
                          ALIAS "thinBasic_VariableExists"        _
                          (                                       _
                            BYVAL vName       AS STRING           _
                          ) AS LONG


  '----------------------------------------------------------------------------
  'thinBasic_VariableGetValueNum
  '----------------------------------------------------------------------------
  ' Returns numeric value of a numeric variable given variable name and optionally array index
  '----------------------------------------------------------------------------
  DECLARE FUNCTION  thinBasic_VariableGetValueNum                 _
                          LIB "thinCore.DLL"                      _
                          ALIAS "thinBasic_VariableGetValueNum"   _
                          (                                       _
                                      BYVAL SearchKey AS STRING , _
                            OPTIONAL  BYVAL lIndex    AS LONG     _
                          ) AS EXT
  '----------------------------------------------------------------------------

  '----------------------------------------------------------------------------
  'thinBasic_VariableGetInfo
  '----------------------------------------------------------------------------
  ' Returns additional variable info giving variable name.
  ' ATTENTION: pass variable as reference. Function will populate
  '            with relevant information
  ' Function returns a pointer to internal thinBAsic variable structure data
  ' that can be used in other situations.
  '----------------------------------------------------------------------------
  DECLARE FUNCTION  thinBasic_VariableGetInfo                     _
                          LIB "thinCore.DLL"                      _
                          ALIAS "thinBasic_VariableGetInfo"       _
                          (                                       _
                            BYVAL SearchKey   AS STRING         , _
                            BYREF MainType    AS LONG           , _       '---ATTENTION: parameter passed BYREF will return info
                            BYREF SubType     AS LONG           , _       '---ATTENTION: parameter passed BYREF will return info
                            BYREF IsArray     AS LONG             _       '---ATTENTION: parameter passed BYREF will return info
                          ) AS LONG

  DECLARE FUNCTION  thinBasic_VariableGetInfoPtr                  _
                          LIB "thinCore.DLL"                      _
                          ALIAS "thinBasic_VariableGetInfoPtr"    _
                          (                                       _
                            BYVAL pVariable   AS LONG           , _       '---A pointer to Variable
                            BYREF MainType    AS LONG           , _       '---ATTENTION: parameter passed BYREF will return info
                            BYREF SubType     AS LONG           , _       '---ATTENTION: parameter passed BYREF will return info
                            BYREF IsArray     AS LONG             _       '---ATTENTION: parameter passed BYREF will return info
                          ) AS LONG

  '----------------------------------------------------------------------------
  'thinBasic_VariableGetInfoEX
  '----------------------------------------------------------------------------
  ' Returns additional variable info giving variable name.
  ' ATTENTION: pass variable as reference. Function will populate
  '            with relevant information
  ' Function returns a pointer to internal thinBAsic variable structure data
  ' that can be used in other situations.
  '----------------------------------------------------------------------------
  DECLARE FUNCTION  thinBasic_VariableGetInfoEX                   _
                          LIB "thinCore.DLL"                      _
                          ALIAS "thinBasic_VariableGetInfoEX"     _
                          (                                       _
                            BYVAL SearchKey   AS STRING         , _
                            BYREF MainType    AS LONG           , _   '---ATTENTION: parameter passed BYREF will return info
                            BYREF SubType     AS LONG           , _   '---ATTENTION: parameter passed BYREF will return info
                            BYREF IsArray     AS LONG           , _   '---ATTENTION: parameter passed BYREF will return info
                            BYREF DataPtr     AS LONG           , _   '---ATTENTION: parameter passed BYREF will return info
                            BYREF nElements   AS LONG           , _   '---ATTENTION: parameter passed BYREF will return info
                            OPTIONAL                              _
                            BYVAL WhichLevel  AS LONG             _
                          ) AS LONG

'  '---Equates for variable Sub Type
'    %SubType_Byte             =  1?
'    %SubType_Integer          =  2?
'    %SubType_Boolean          =  2?
'    %SubType_Word             =  3?
'    %SubType_DWord            =  4?
'    %SubType_Long             =  5?
'    %SubType_Quad             =  6?
'    %SubType_Single           =  7?
'    %SubType_Double           =  8?
'    %SubType_Currency         =  9?
'    %SubType_Ext              = 10?
'
'    %MainType_IsNumber        = 15?
'
'    %SubType_AsciiZ           = 16?
'    %SubType_String           = 17?
'
'    %MainType_GUID            = 20?               : %MainType_IsGUID    = %MainType_GUID
'    %MainType_String          = %SubType_String   : %MainType_IsString  = %MainType_String
'
'    %MainType_Variant         = 23?               : %MainType_IsVariant = %MainType_Variant
'    %MainType_UDT             = 24?               : %MainType_IsUDT     = %MainType_UDT
'    %MainType_PTR             = 25?               : %MainType_IsPTR     = %MainType_PTR
'    %MainType_Object          = 26?               : %MainType_IsObject  = %MainType_Object
'    %MainType_Class           = 27?               : %MainType_IsClass   = %MainType_Class
  '---Equates for variable Sub Type
    %SubType_Byte             =  1?
    %SubType_Integer          =  2?
    %SubType_Boolean          =  2?
    %SubType_Word             =  3?
    %SubType_DWord            =  4?
    %SubType_Long             =  5?
    %SubType_Quad             =  6?
    %SubType_Single           =  7?
    %SubType_Double           =  8?
    %SubType_Currency         =  9?
    %SubType_Ext              = 10?

    %MainType_IsNumber        = 20?

    %SubType_AsciiZ           = 25?
    %SubType_String           = 30?

    %MainType_GUID            = 40?               : %MainType_IsGUID    = %MainType_GUID
    %MainType_String          = %SubType_String   : %MainType_IsString  = %MainType_String

    %MainType_Variant         = 50?               : %MainType_IsVariant = %MainType_Variant
    %MainType_UDT             = 60?               : %MainType_IsUDT     = %MainType_UDT
    %MainType_PTR             = 70?               : %MainType_IsPTR     = %MainType_PTR
    %MainType_Object          = 80?               : %MainType_IsObject  = %MainType_Object
    %MainType_Class           = 90?               : %MainType_IsClass   = %MainType_Class
    %MainType_Function        = 95?               : %MainType_IsFunction= %MainType_Function




  '----------------------------------------------------------------------------
  'thinBasic_VariableIsArray
  '----------------------------------------------------------------------------
  ' Returns true/false depending if given name is an array
  '----------------------------------------------------------------------------
  DECLARE FUNCTION  thinBasic_VariableIsArray                     _
                          LIB "thinCore.DLL"                      _
                          ALIAS "thinBasic_VariableIsArray"       _
                          (                                       _
                            BYVAL vName       AS STRING           _
                          ) AS LONG

  '----------------------------------------------------------------------------
  'thinBasic_VariableRedim
  '----------------------------------------------------------------------------
  ' Redim a variable giving variable ptr
  '----------------------------------------------------------------------------
  DECLARE FUNCTION  thinBasic_VariableRedim                       _
                          LIB "thinCore.DLL"                      _
                          ALIAS "thinBasic_VariableRedim"         _
                          (                                       _
                            BYVAL pVar AS LONG,                   _
                            BYVAL lPreserve AS LONG,              _
                            BYVAL VarDim1 AS LONG,                _
                            BYVAL VarDim2 AS LONG,                _
                            BYVAL VarDim3 AS LONG                 _
                          ) AS LONG

  '----------------------------------------------------------------------------
  'thinBasic_ArrayGetElements
  '----------------------------------------------------------------------------
  ' Returns total number of elements inside an array giving the array name
  ' ATTENTION: this function works on single or multi dimensions arrays
  '----------------------------------------------------------------------------
  DECLARE FUNCTION  thinBasic_ArrayGetElements                    _
                          LIB "thinCore.DLL"                      _
                          ALIAS "thinBasic_ArrayGetElements"      _
                          (                                       _
                            BYVAL vName       AS STRING           _
                          ) AS LONG

  '----------------------------------------------------------------------------
  'thinBasic_ArrayGetPtr
  '----------------------------------------------------------------------------
  ' Returns the data structure pointer of an array giving its name
  '----------------------------------------------------------------------------
  DECLARE FUNCTION  thinBasic_ArrayGetPtr                         _
                          LIB "thinCore.DLL"                      _
                          ALIAS "thinBasic_ArrayGetPtr"           _
                          (                                       _
                            BYVAL vName       AS STRING           _
                          ) AS LONG

  '----------------------------------------------------------------------------
  'thinBasic_ArrayGetInfo
  '----------------------------------------------------------------------------
  ' Returns information on an array passing array pointer returned by thinBasic_ArrayGetPtr
  '----------------------------------------------------------------------------
  DECLARE FUNCTION  thinBasic_ArrayGetInfo                        _
                          LIB "thinCore.DLL"                      _
                          ALIAS "thinBasic_ArrayGetInfo"          _
                          (                                       _
                            BYVAL ArrayPtr    AS LONG,            _
                            BYVAL InfoType    AS LONG             _
                          ) AS LONG

  '---Equates for InfoType
    %Array_ElementsCount        =  1&     'Total number of elements in the array
    %Array_ElementSize          =  2&     'The size of the single element (for example an array of LONGs will return 4)
    %Array_Dimensions           =  3&     'Number of dimensions (from 1 to 3)
    %Array_Size                 =  4&     'Memory size allocated for the array. This will not compute the memory needed for strings
    %Array_ElementsType         = 10&     'Type of elements strored into the array. See equates for thinBasic_VariableGetInfo
    %Array_ElementsAreFixed     = 15&     '%TRUE if elements are fixed size, like fixed strings or UDT
    %Array_PtrToData            = 30&     'Pointer to memory area holding data

    %Array_UBoundDim_1          = 91&     'Returns the Upper Bound of dimension 1
    %Array_UBoundDim_2          = 92&     'Returns the Upper Bound of dimension 2
    %Array_UBoundDim_3          = 93&     'Returns the Upper Bound of dimension 3
  '----------------------------------------------------------------------------
  'thinBasic_AddEquate
  '----------------------------------------------------------------------------
  ' Add a new equate (constant)
  '----------------------------------------------------------------------------
  DECLARE FUNCTION  thinBasic_AddEquate                           _
                          LIB "thinCore.DLL"                      _
                          ALIAS "thinBasic_AddEquate"             _
                          (                                       _
                            BYVAL vName       AS STRING,          _
                            BYVAL lValString  AS STRING,          _
                            BYVAL lValNumber  AS EXT   ,          _
                            OPTIONAL                              _
                            BYVAL ForceType   AS LONG             _
                          ) AS LONG

  '---Used for thinBasic_AddEquate to force an equate type in case of missing first char $ or %
  %EquateTypeNumber    = 3
  %EquateTypeString    = 5

  '----------------------------------------------------------------------------
  'thinBasic_AddVariable
  '----------------------------------------------------------------------------
  ' Add a new variable to current stack level
  '----------------------------------------------------------------------------
  DECLARE FUNCTION  thinBasic_AddVariable                         _
                          LIB "thinCore.DLL"                      _
                          ALIAS "thinBasic_AddVariable"           _
                          (                                       _
                            BYVAL vName       AS STRING,          _
                            BYVAL lValString  AS STRING,          _
                            BYVAL lValNumber  AS EXT   ,          _
                            BYVAL ForceType   AS LONG  ,          _
                   OPTIONAL BYVAL VarMemPtr   AS LONG  ,          _
                            BYVAL Reserved1   AS LONG  ,          _
                            BYVAL Reserved2   AS LONG  ,          _
                            BYVAL Reserved3   AS LONG  ,          _
                            BYVAL Reserved4   AS LONG             _
                          ) AS LONG

  '----------------------------------------------------------------------------
  'thinBasic_AddUdt
  '----------------------------------------------------------------------------
  ' Add a new UDT structure
  '----------------------------------------------------------------------------
  DECLARE FUNCTION  thinBasic_AddUdt                              _
                          LIB "thinCore.DLL"                      _
                          ALIAS "thinBasic_AddUdt"                _
                          (                                       _
                            BYVAL sUDT_Code   AS STRING           _
                          ) AS LONG

  '----------------------------------------------------------------------------
  'thinBasic_DeclareFunction
  '----------------------------------------------------------------------------
  ' Add a new function using DECLARE statement and function pointer
  '----------------------------------------------------------------------------
  DECLARE FUNCTION thinBasic_DeclareFunction                      _
                          LIB "thinCore.DLL"                      _
                          ALIAS "thinBasic_DeclareFunction"       _
                          (                                       _
                            BYVAL sDeclare AS STRING    ,         _
                            BYVAL pFun AS DWORD                   _
                          ) AS LONG

  '----------------------------------------------------------------------------
  'thinBasic_ChangeVariableNumber
  '----------------------------------------------------------------------------
  ' Change the value of a numeric variable giving its name a the new value
  '----------------------------------------------------------------------------
  DECLARE FUNCTION  thinBasic_ChangeVariableNumber                _
                          LIB "thinCore.DLL"                      _
                          ALIAS "thinBasic_ChangeVariableNumber"  _
                          (                                       _
                            BYVAL vName       AS STRING,          _
                            BYVAL lValNumber  AS EXT              _
                          ) AS LONG

  '----------------------------------------------------------------------------
  'thinBasic_ChangeVariableString
  '----------------------------------------------------------------------------
  ' Change the value of a string variable giving its name a the new value
  '----------------------------------------------------------------------------
  DECLARE FUNCTION  thinBasic_ChangeVariableString                _
                          LIB "thinCore.DLL"                      _
                          ALIAS "thinBasic_ChangeVariableString"  _
                          (                                       _
                            BYVAL vName       AS STRING,          _
                            BYVAL lValNumber  AS STRING           _
                          ) AS LONG


  '----------------------------------------------------------------------------
  'thinBasic_GetToken
  '----------------------------------------------------------------------------
  ' Returns the next token as token ID.
  '----------------------------------------------------------------------------
  DECLARE FUNCTION  thinBasic_GetToken                            _
                          LIB "thinCore.DLL"                      _
                          ALIAS "thinBasic_GetToken"              _
                          (                                       _
                            OPTIONAL BYVAL AutoPutBack AS LONG    _
                          ) AS LONG

  '----------------------------------------------------------------------------
  'thinBasic_GetToken
  '----------------------------------------------------------------------------
  ' Returns the next token as string.
  '----------------------------------------------------------------------------
  DECLARE FUNCTION  thinBasic_GetTokenName                        _
                          LIB "thinCore.DLL"                      _
                          ALIAS "thinBasic_GetTokenName"          _
                          (                                       _
                            OPTIONAL BYVAL AutoPutBack AS LONG    _
                          ) AS STRING

  '----------------------------------------------------------------------------
  'thinBasic_GetTokenID
  '----------------------------------------------------------------------------
  ' Return internal engine unique ID giving the token name
  '----------------------------------------------------------------------------
  DECLARE FUNCTION  thinBasic_GetTokenID                          _
                          LIB "thinCore.DLL"                      _
                          ALIAS "thinBasic_GetTokenID"            _
                          (                                       _
                            BYVAL TokenName AS STRING             _
                          ) AS LONG


  '----------------------------------------------------------------------------
  'thinBasic_TokenGetCurrentID
  '----------------------------------------------------------------------------
  ' Return current token ID
  '----------------------------------------------------------------------------
  DECLARE FUNCTION  thinBasic_TokenGetCurrentID                   _
                          LIB "thinCore.DLL"                      _
                          ALIAS "thinBasic_TokenGetCurrentID"     _
                          () AS LONG

  '----------------------------------------------------------------------------
  'thinBasic_PutBack
  '----------------------------------------------------------------------------
  ' Put back into parsing stack the last parsed token
  '----------------------------------------------------------------------------
  DECLARE FUNCTION thinBasic_Putback                              _
                          LIB "thinCore.DLL"                      _
                          ALIAS "thinBasic_PutBack"               _
                          (                                       _
                            OPTIONAL BYVAL lPtr AS LONG           _
                          ) AS LONG

  '----------------------------------------------------------------------------
  'thinBasic_FunctionExists
  '----------------------------------------------------------------------------
  '----------------------------------------------------------------------------
  DECLARE FUNCTION  thinBasic_FunctionExists                      _
                          LIB "thinCore.DLL"                      _
                          ALIAS "thinBasic_FunctionExists"        _
                          (                                       _
                            BYVAL fName       AS STRING           _
                          ) AS LONG

  '----------------------------------------------------------------------------
  'thinBasic_FunctionGetPtr
  '----------------------------------------------------------------------------
  '----------------------------------------------------------------------------
  DECLARE FUNCTION  thinBasic_FunctionGetPtr                      _
                          LIB "thinCore.DLL"                      _
                          ALIAS "thinBasic_FunctionGetPtr"        _
                          (                                       _
                            BYVAL fName       AS STRING           _
                          ) AS LONG

  '----------------------------------------------------------------------------
  'thinBasic_FunctionGetPtr
  '----------------------------------------------------------------------------
  '----------------------------------------------------------------------------
  DECLARE FUNCTION  thinBasic_FunctionGetName                     _
                          LIB "thinCore.DLL"                      _
                          ALIAS "thinBasic_FunctionGetName"       _
                          (                                       _
                            BYVAL FunctionPtr AS LONG             _  '---PTR to function returned by (for example) thinBasic_FunctionGetPtr
                          ) AS STRING


  '----------------------------------------------------------------------------
  'thinBasic_FunctionIsCallBack
  '----------------------------------------------------------------------------
  ' Determine if fucntion passed as PTR has been defined as CALLBACK function in script
  '----------------------------------------------------------------------------
  DECLARE FUNCTION  thinBasic_FunctionIsCallBack                  _
                          LIB "thinCore.DLL"                      _
                          ALIAS "thinBasic_FunctionIsCallBack"    _
                          (                                       _
                            BYVAL FunctionPtr AS LONG             _  '---PTR to function returned by thinBasic_FunctionGetPtr
                          ) AS LONG


  '----------------------------------------------------------------------------
  'thinBasic_FunctionGetCBParam
  '----------------------------------------------------------------------------
  ' Returns the value of a designated CallBack pseudo variable.
  ' ATTENTION: interface function valid only whileinside a callback function
  '----------------------------------------------------------------------------
  ' Parameters:
  '   CBParamType: one of the following equates
        '---Equates for CBParamType
        %CBParam_CBHNDL       = 100&
        %CBParam_CBMSG        = 110&
        %CBParam_CBCTL        = 120&
        %CBParam_CBCTLMSG     = 130&
        %CBParam_CBLPARAM     = 140&
        %CBParam_CBWPARAM     = 150&
        %CBParam_CBNMCODE     = 160&
        %CBParam_CBNMHDR      = 170&
        %CBParam_CBNMHWND     = 180&
        %CBParam_CBNMID       = 190&
  '   lError: a pointer to a long variable that will receive possible error variables
  '           Possible errors:
  '                            -10: not inside at any function
  '                            -20: inside a function but not a callback function
  '                            -30: unsupported/invalid CBParamType
  '----------------------------------------------------------------------------
  DECLARE FUNCTION thinBasic_FunctionGetCBParam                     _
                          LIB "thinCore.DLL"                        _
                          ALIAS "thinBasic_FunctionGetCBParam"      _
                          (                                         _
                                      BYVAL CBParamType AS LONG   , _
                            OPTIONAL  BYVAL lError AS LONG PTR      _
                          ) AS LONG

  '----------------------------------------------------------------------------
  'thinBasic_FunctionGetNumberOfParams
  '----------------------------------------------------------------------------
  ' Returns the number of parameters defined in a script function
  '----------------------------------------------------------------------------
  DECLARE FUNCTION  thinBasic_FunctionGetNumberOfParams           _
                          LIB "thinCore.DLL"                      _
                          ALIAS "thinBasic_FunctionGetNumberOfParams"     _
                          (                                       _
                            BYVAL FunctionPtr AS LONG             _  '---PTR to function returned by thinBasic_FunctionGetPtr
                          ) AS LONG

  '----------------------------------------------------------------------------
  'thinBasic_FunctionGetReturnMainType
  '----------------------------------------------------------------------------
  ' Gets the main data type returned by a script function. See %VarMainType* equates above
  '----------------------------------------------------------------------------
  DECLARE FUNCTION  thinBasic_FunctionGetReturnMainType           _
                          LIB "thinCore.DLL"                      _
                          ALIAS "thinBasic_FunctionGetReturnMainType"     _
                          (                                       _
                            BYVAL FunctionPtr AS LONG             _  '---PTR to function returned by thinBasic_FunctionGetPtr
                          ) AS LONG

  '----------------------------------------------------------------------------
  'thinBasic_FunctionParseAndGetPtr
  '----------------------------------------------------------------------------
  ' Parse the next token (or string expression). Check if it is a function name
  ' If yes, returns a PTR to internal data function
  '----------------------------------------------------------------------------
  DECLARE FUNCTION thinBasic_FunctionParseAndGetPtr                 _
                          LIB "thinCore.DLL"                        _
                          ALIAS "thinBasic_FunctionParseAndGetPtr"  _
                          (                                         _
                            OPTIONAL BYVAL CheckIfCallBack AS LONG  _
                          ) AS LONG

  '----------------------------------------------------------------------------
  'thinBasic_FunctionSimpleCall
  '----------------------------------------------------------------------------
  ' Call a script function and optionally returns it value (numeric or string)
  '----------------------------------------------------------------------------
  DECLARE FUNCTION  thinBasic_FunctionSimpleCall                  _
                          LIB "thinCore.DLL"                      _
                          ALIAS "thinBasic_FunctionSimpleCall"    _
                          (                                       _
                            BYVAL FunctionName AS STRING,         _  '---Name of the function
                            OPTIONAL                              _
                            BYVAL ptrEXT AS EXT PTR,              _  '---Used to get back from the called function a numeric value
                            BYVAL ptrSTR AS STRING PTR            _  '---Used to get back from the called function a string value
                          ) AS LONG

  '----------------------------------------------------------------------------
  'thinBasic_FunctionSimpleCall_ByPtr
  '----------------------------------------------------------------------------
  ' Call a script function and optionally returns it value (numeric or string)
  ' This function permits to call script callback functions passing automatic
  ' pseudo callbacks variables
  ' USE only when in need of a callback function from module
  '----------------------------------------------------------------------------
  DECLARE FUNCTION  thinBasic_FunctionSimpleCall_ByPtr                _
                          LIB "thinCore.DLL"                          _
                          ALIAS "thinBasic_FunctionSimpleCall_ByPtr"  _
                          (                                           _
                            BYVAL FunctionPtr AS LONG               , _  '---PTR to function returned by thinBasic_FunctionGetPtr or other way
                            OPTIONAL                                  _
                            BYVAL ptrEXT      AS EXT PTR            , _  '---Used to get back from the called function a numeric value
                            BYVAL ptrSTR      AS STRING PTR         , _  '---Used to get back from the called function a string value
                            BYVAL IsCallBack  AS LONG               , _
                            BYVAL lCBHNDL     AS LONG               , _
                            BYVAL lCBMSG      AS LONG               , _
                            BYVAL lCBCTL      AS LONG               , _
                            BYVAL lCBCTLMSG   AS LONG               , _
                            BYVAL lCBLPARAM   AS LONG               , _
                            BYVAL lCBWPARAM   AS LONG               , _
                            BYVAL lCBNMCODE   AS LONG               , _
                            BYVAL lCBNMHDR    AS LONG               , _
                            BYVAL lCBNMHWND   AS LONG               , _
                            BYVAL lCBNMID     AS LONG                 _
                          ) AS LONG

  '----------------------------------------------------------------------------
  'thinBasic_FunctionCall_ByPtr
  '----------------------------------------------------------------------------
  ' Call a script function and optionally returns it value (numeric or string)
  ' This function permits to call script functions passing parameters
  ' Parameters are passed using a shared memory area made by a sequence of DOUBLEs
  ' (8 bytes) one for each parameter to be passed.
  ' The paramaters memory area will be interpreted by thinBasic core engine
  ' depending by parameters declaration made in script.
  '
  ' So far the following type of parameters are supported:
  '   - numeric parameters passed BYVAL up to DOUBLE range
  '
  ' Example: if programmer wants to pass 2 parameters, set lModParams = 2 and setup
  ' a 16 bytes memory area (2 params * 8 bytes each) where to store the 2 parameter
  ' values.
  '----------------------------------------------------------------------------
  DECLARE FUNCTION  thinBasic_FunctionCall_ByPtr                      _
                          LIB "thinCore.DLL"                          _
                          ALIAS "thinBasic_FunctionCall_ByPtr"        _
                          (                                           _
                            BYVAL FunctionPtr   AS LONG             , _  '---PTR to script function
                            BYVAL lModParams    AS LONG             , _  '---MANDATORY: number of params module is passing
                            BYVAL lModParamsPtr AS LONG             , _  '---MANDATORY: pointer to a memory area where to find parameters (8 bytes for each parameter)
                            OPTIONAL                                  _  '---If no need to get back script function result value, do not indicate the next 2 parameters
                            BYVAL ptrDOUBLE     AS DOUBLE PTR       , _  '---Pointer to DOUBLE that will get back script function return value in case of numeric
                            BYVAL ptrSTR        AS STRING PTR         _  '---Pointer to a OLE32 dynamic string handle that will get back script function return value in case of string
                          ) AS LONG

  '----------------------------------------------------------------------------
  'thinBasic_GetKeywordSpeficic
  '----------------------------------------------------------------------------
  ' Instruct parser to get next token, test if it a keyword and if yes,
  ' check if it is one of the possible keywords passed. If not, a RT-Error
  ' will be generated
  '----------------------------------------------------------------------------
  DECLARE FUNCTION  thinBasic_GetKeywordSpeficic                  _
                          LIB "thinCore.DLL"                      _
                          ALIAS "thinBasic_GetKeywordSpeficic"    _
                          (                                       _
                                      BYVAL HideError   AS LONG , _
                                      BYVAL AutoPutBack AS LONG , _
                                      BYVAL lKey1   AS LONG     , _
                             OPTIONAL BYVAL lKey2   AS LONG     , _
                                      BYVAL lKey3   AS LONG     , _
                                      BYVAL lKey4   AS LONG     , _
                                      BYVAL lKey5   AS LONG     , _
                                      BYVAL lKey6   AS LONG     , _
                                      BYVAL lKey7   AS LONG     , _
                                      BYVAL lKey8   AS LONG     , _
                                      BYVAL lKey9   AS LONG     , _
                                      BYVAL lKey10  AS LONG     , _
                                      BYVAL lKey11  AS LONG     , _
                                      BYVAL lKey12  AS LONG     , _
                                      BYVAL lKey13  AS LONG     , _
                                      BYVAL lKey14  AS LONG     , _
                                      BYVAL lKey15  AS LONG     , _
                                      BYVAL lKey16  AS LONG     , _
                                      BYVAL lKey17  AS LONG     , _
                                      BYVAL lKey18  AS LONG     , _
                                      BYVAL lKey19  AS LONG     , _
                                      BYVAL lKey20  AS LONG     , _
                                      BYVAL lKey21  AS LONG     , _
                                      BYVAL lKey22  AS LONG     , _
                                      BYVAL lKey23  AS LONG     , _
                                      BYVAL lKey24  AS LONG     , _
                                      BYVAL lKey25  AS LONG       _
                          ) AS LONG

  '----------------------------------------------------------------------------
  'thinBasic_GetKeywordSpeficic_Single
  '----------------------------------------------------------------------------
  ' Instruct parser to get next token, test if it a keyword and if yes,
  ' check if it is the one requested keyword. If not, a RT-Error
  ' will be generated
  '----------------------------------------------------------------------------
  DECLARE FUNCTION  thinBasic_GetKeywordSpeficic_Single                  _
                          LIB "thinCore.DLL"                      _
                          ALIAS "thinBasic_GetKeywordSpeficic_Single"    _
                          (                                       _
                                      BYVAL HideError   AS LONG , _
                                      BYVAL AutoPutBack AS LONG , _
                                      BYVAL lKey1       AS LONG   _
                          ) AS LONG

  '----------------------------------------------------------------------------
  'thinBasic_VariableParse
  '----------------------------------------------------------------------------
  ' Instruct parser to get next token, check if variable, check if array and
  ' return info needed to subsequent change variable value
  '----------------------------------------------------------------------------
  DECLARE FUNCTION  thinBasic_VariableParse                       _
                          LIB "thinCore.DLL"                      _
                          ALIAS "thinBasic_VariableParse"         _
                          (                                       _
                            BYREF VariablePtr     AS LONG       , _     '---ATTENTION: parameter passed BYREF will return info
                            BYREF VariableAbsPos  AS LONG         _     '---ATTENTION: parameter passed BYREF will return info
                          ) AS LONG

  '----------------------------------------------------------------------------
  'thinBasic_VariableParsePtr
  '----------------------------------------------------------------------------
  ' Instruct parser to get next token, check if variable
  ' return its pointer
  '----------------------------------------------------------------------------
  DECLARE FUNCTION  thinBasic_VariableParsePtr                    _
                          LIB "thinCore.DLL"                      _
                          ALIAS "thinBasic_VariableParsePtr"      _
                          (                                       _
                            BYREF VariablePtr     AS LONG         _     '---ATTENTION: parameter passed BYREF will return info
                          ) AS LONG

  '----------------------------------------------------------------------------
  'thinBasic_ParsePtrToSomething
  '----------------------------------------------------------------------------
  ' Parse whatever and return a PTR to something
  '----------------------------------------------------------------------------
  DECLARE FUNCTION thinBasic_ParsePtrToSomething                    _
                          LIB "thinCore.DLL"                        _
                          ALIAS "thinBasic_ParsePtrToSomething"     _
                          (                                         _
                            BYREF VariablePtr AS LONG               _   '---ATTENTION: parameter passed BYREF will return info
                          ) AS LONG

  '----------------------------------------------------------------------------
  'thinBasic_VariablePtrToDirectPtr
  '----------------------------------------------------------------------------
  ' Convert a variable ptr to its internal ptr
  '----------------------------------------------------------------------------
  DECLARE FUNCTION  thinBasic_VariablePtrToDirectPtr                _
                          LIB "thinCore.DLL"                        _
                          ALIAS "thinBasic_VariablePtrToDirectPtr"  _
                          (                                         _
                            BYVAL VariablePtr     AS LONG           _
                          ) AS LONG

  '----------------------------------------------------------------------------
  'thinBasic_DirectPtrToDataPtr
  '----------------------------------------------------------------------------
  ' Convert a variable ptr to its data ptr
  '----------------------------------------------------------------------------
  DECLARE FUNCTION  thinBasic_DirectPtrToDataPtr                    _
                          LIB "thinCore.DLL"                        _
                          ALIAS "thinBasic_DirectPtrToDataPtr"      _
                          (                                         _
                            BYVAL DirectPtr       AS LONG           _
                          ) AS LONG

  '----------------------------------------------------------------------------
  'thinBasic_VariableParseAndGetInfo
  '----------------------------------------------------------------------------
  '
  '----------------------------------------------------------------------------
  DECLARE FUNCTION thinBasic_VariableParseAndGetInfo                _
                          LIB "thinCore.DLL"                        _
                          ALIAS "thinBasic_VariableParseAndGetInfo" _
                          (                                         _
                            BYREF VariableName    AS STRING       , _   '---ATTENTION: parameter passed BYREF will return info
                            BYREF VariablePtr     AS LONG         , _   '---ATTENTION: parameter passed BYREF will return info
                            BYREF MainType        AS LONG         , _   '---ATTENTION: parameter passed BYREF will return info
                            BYREF SubType         AS LONG         , _   '---ATTENTION: parameter passed BYREF will return info
                            BYREF DataPtr         AS LONG         , _   '---ATTENTION: parameter passed BYREF will return info
                            BYREF nElements       AS LONG           _   '---ATTENTION: parameter passed BYREF will return info
                          ) AS LONG


  '----------------------------------------------------------------------------
  'thinBasic_ParseVariableInfo
  '----------------------------------------------------------------------------
  ' Parameters (all passed BYREF ... AS LONG):
  '   - VariablePtr       pointer to internal thinBasic Core engine data structure
  '                       used to store variable info
  '   - MainType          variable main type
  '   - SubType           variable sub type
  '   - ElementsAreFixed  %TRUE if elements inside data buffer are fixed size.
  '                       For example will return %TRUE:
  '                         - fixed STRING size, the one declared ... AS STRING * size
  '                         - fixed ASCIIZ size, the one declared ... AS ASCIIZ * size
  '                         - UDT variables
  '   - TotElements       total number of elements in variable. Usually 1 if
  '                       variable is not an array
  '   - ElementSize       size of the single element. For example if variable is a
  '                       LONG, ElementSize = 4. If EXT ElementSize = 10
  '                       if variable is a UDT, it will depend from UDT to UDT.
  '   - DataPtr           pointer to variable data
  '   - AbsPos            absolute position inside the array if variable is an array
  '                       if variable is not an array 1 is returned
  '----------------------------------------------------------------------------
  DECLARE FUNCTION thinBasic_ParseVariableInfo                      _
                          LIB "thinCore.DLL"                        _
                          ALIAS "thinBasic_ParseVariableInfo"       _
                          (                                         _
                            BYREF VariablePtr       AS LONG           , _   '---ATTENTION: parameter passed BYREF will return info
                            BYREF MainType          AS LONG           , _   '---ATTENTION: parameter passed BYREF will return info
                            BYREF SubType           AS LONG           , _   '---ATTENTION: parameter passed BYREF will return info
                            BYREF ElementsAreFixed  AS LONG           , _   '---ATTENTION: parameter passed BYREF will return info
                            BYREF TotElements       AS LONG           , _   '---ATTENTION: parameter passed BYREF will return info
                            BYREF ElementSize       AS LONG           , _   '---ATTENTION: parameter passed BYREF will return info
                            BYREF DataPtr           AS LONG           , _   '---ATTENTION: parameter passed BYREF will return info
                            BYREF AbsPos            AS LONG             _   '---ATTENTION: parameter passed BYREF will return info
                          ) AS LONG
  '------------------------------------------------------------------------------

'  '----------------------------------------------------------------------------
'  'thinBasic_ParseVariableInfo_EX
'  '----------------------------------------------------------------------------
'  ' Parameters (all passed BYREF ... AS LONG):
'  '   - VariablePtr       pointer to internal thinBasic Core engine data structure
'  '                       used to store variable info
'  '   - MainType          variable main type
'  '   - SubType           variable sub type
'  '   - ElementsAreFixed  %TRUE if elements inside data buffer are fixed size.
'  '                       For example will return %TRUE:
'  '                         - fixed STRING size, the one declared ... AS STRING * size
'  '                         - fixed ASCIIZ size, the one declared ... AS ASCIIZ * size
'  '                         - UDT variables
'  '   - TotElements       total number of elements in variable. Usually 1 if
'  '                       variable is not an array
'  '   - ElementSize       size of the single element. For example if variable is a
'  '                       LONG, ElementSize = 4. If EXT ElementSize = 10
'  '                       if variable is a UDT, it will depend from UDT to UDT.
'  '   - DataPtr           pointer to variable data
'  '   - AbsPos            absolute position inside the array if variable is an array
'  '                       if variable is not an array 1 is returned
'  '----------------------------------------------------------------------------
'  Declare Function thinBasic_ParseVariableInfo_EX                         _
'                          Lib "thinCore.DLL"                              _
'                          Alias "thinBasic_ParseVariableInfo_EX"          _
'                          (                                               _
'                            ByRef VariablePtr                 As Long   , _   '---ATTENTION: parameter passed BYREF will return info
'                            ByRef MainType                    As Long   , _   '---ATTENTION: parameter passed BYREF will return info
'                            ByRef SubType                     As Long   , _   '---ATTENTION: parameter passed BYREF will return info
'                            ByRef ElementsAreFixed            As Long   , _   '---ATTENTION: parameter passed BYREF will return info
'                            ByRef TotElements                 As Long   , _   '---ATTENTION: parameter passed BYREF will return info
'                            ByRef ElementSize                 As Long   , _   '---ATTENTION: parameter passed BYREF will return info
'                            ByRef DataPtr                     As Long   , _   '---ATTENTION: parameter passed BYREF will return info
'                            ByRef AbsPos                      As Long   , _   '---ATTENTION: parameter passed BYREF will return info
'                            ByVal Param_AbsPosCanBeMissed     As Long   , _
'                            ByRef Param_nDims                 As Long   , _
'                            ByRef Param_Dim1UBound            As Long   , _
'                            ByRef Param_Dim2UBound            As Long   , _
'                            ByRef Param_Dim3UBound            As Long     _
'                          ) As Long
'  '------------------------------------------------------------------------------

  '----------------------------------------------------------------------------
  'thinBasic_ChangeVariableStringDirect
  '----------------------------------------------------------------------------
  ' See also thinBasic_VariableParse
  '
  ' Change a variable using direct variable pointer's data returned by
  ' thinBasic_VariableParse. This will ensure to work also with arrays
  '----------------------------------------------------------------------------
  DECLARE FUNCTION  thinBasic_ChangeVariableStringDirect          _
                          LIB "thinCore.DLL"                      _
                          ALIAS "thinBasic_ChangeVariableStringDirect" _
                          (                                       _
                            BYVAL VariablePtr     AS LONG       , _
                            BYVAL VariableAbsPos  AS LONG       , _
                            BYVAL lValString      AS STRING       _
                          ) AS LONG

  '----------------------------------------------------------------------------
  'thinBasic_ChangeVariableNumberDirect
  '----------------------------------------------------------------------------
  ' See also thinBasic_VariableParse
  '
  ' Change a variable using direct variable pointer's data returned by
  ' thinBasic_VariableParse. This will ensure to work also with arrays
  '----------------------------------------------------------------------------
  DECLARE FUNCTION  thinBasic_ChangeVariableNumberDirect          _
                          LIB "thinCore.DLL"                      _
                          ALIAS "thinBasic_ChangeVariableNumberDirect" _
                          (                                       _
                            BYVAL VariablePtr     AS LONG       , _
                            BYVAL VariableAbsPos  AS LONG       , _
                            BYVAL lValNumber      AS EXT          _
                          ) AS LONG


  '----------------------------------------------------------------------------
  'thinBasic_GetVariableNumberDirect
  '----------------------------------------------------------------------------
  '
  ' Returns the value of a variable giving its ptr and it abs position
  '----------------------------------------------------------------------------
  DECLARE FUNCTION thinBasic_GetVariableNumberDirect              _
                          LIB "thinCore.DLL"                      _
                          ALIAS "thinBasic_GetVariableNumberDirect" _
                          (                                       _
                            BYVAL VariablePtr     AS LONG       , _
                            BYVAL VariableAbsPos  AS LONG         _
                          ) AS EXT

  '----------------------------------------------------------------------------
  'thinBasic_ChangeVariableUDTDirect
  '----------------------------------------------------------------------------
  ' See also thinBasic_VariableParse
  '
  ' Change a variable using direct variable pointer's data returned by
  ' thinBasic_VariableParse. This will ensure to work also with arrays
  '----------------------------------------------------------------------------
  DECLARE FUNCTION  thinBasic_ChangeVariableUDTDirect          _
                          LIB "thinCore.DLL"                      _
                          ALIAS "thinBasic_ChangeVariableUDTDirect" _
                          (                                       _
                            BYVAL VariablePtr     AS LONG       , _
                            BYVAL VariableAbsPos  AS LONG       , _
                            BYVAL lValString      AS STRING       _
                          ) AS LONG


  '----------------------------------------------------------------------------
  ' NOTE
  '----------------------------------------------------------------------------
  ' The following functions
  '
  '    thinBasic_ParseNumber
  '    thinBasic_ParseString
  '    thinBasic_CheckOpenParens
  '    thinBasic_CheckCloseParens
  '    thinBasic_CheckComma
  '
  ' are used inside user defined functions/subs to parse function params.
  ' Imagine you want create a user def function like:
  '
  '    MyFunct(String1, String2, Number1)
  '
  ' To get params you have to parse the following tokens:
  '    (           Open parens
  '      String1     a string expression
  '      ,           a comma
  '      String2     a second string expression
  '      ,           another comma
  '      Number1     a numeric expression
  '    )           Finally close parens
  '
  ' thinBasic gives this ability using 5 simple functions to parse user expressions.
  ' Let's take again the above example and see how to write a user defined
  ' function that returns a STRING
  '
  ' FUNCTION MyLeft() AS STRING
  ' 'Syntax: Number = MyLeft(S1, S2, N1)
  '   LOCAL lString1 AS STRING                           'Define first string param
  '   LOCAL lString2 AS STRING                           'Define second string param
  '   LOCAL lNumber1 AS EXT                              'Define third number param
  '   IF thinBasic_CheckOpenParens THEN                  'Check if open parens token found
  '     thinBasic_ParseString lString1                   'Now evaluate a string expression
  '     IF thinBasic_CheckComma THEN                     'Check if there is a comma
  '       thinBasic_ParseString lString2                 'Parse another string expression
  '       IF thinBasic_CheckComma THEN                   'Another comma
  '         thinBasic_ParseNumber lNumber1               'Now get a numeric expression
  '         IF thinBasic_CheckCloseParens THEN           'Finally a close parens
  '           FUNCTION = LEFT$(lString1, lNumber1) + _   '...here we are. Here you can assign
  '                      LEFT$(lString2, lNumber1)       '...to your function whatever value
  '         END IF                                       '...using the evaluated params
  '       END IF
  '     END IF
  '   END IF
  ' END FUNCTION
  '
  '
  ' thinBasic_CheckOpenParens
  ' thinBasic_CheckCloseParens
  ' thinBasic_CheckComma
  ' have the following optional parameters:
  '
  '   HideHerror
  '               if %TRUE, in case of parsing problems, no runtime error will
  '               be generated
  '   AutoPutBack
  '               if %TRUE, in case of parsing problems, the found token
  '               will be put back into parsing stack
  '
  '----------------------------------------------------------------------------
  DECLARE SUB       thinBasic_ParseNumber                 LIB "thinCore.DLL" ALIAS "thinBasic_ParseNumber"                (Result AS EXT)
  DECLARE SUB       thinBasic_ParseLong                   LIB "thinCore.DLL" ALIAS "thinBasic_ParseLong"                  (Result AS LONG)
  DECLARE SUB       thinBasic_ParseDWord                  LIB "thinCore.DLL" ALIAS "thinBasic_ParseDWord"                 (Result AS DWORD)
  DECLARE FUNCTION  thinBasic_ParseLong_Optional          LIB "thinCore.DLL" ALIAS "thinBasic_ParseLong"                  (Result AS LONG) AS LONG
  '---

  DECLARE FUNCTION  thinBasic_Parse1Number                LIB "thinCore.DLL" ALIAS "thinBasic_Parse1Number"               () AS EXT
  DECLARE FUNCTION  thinBasic_Parse2Numbers               LIB "thinCore.DLL" ALIAS "thinBasic_Parse2Numbers"              (Num1 AS EXT, Num2 AS EXT) AS EXT
  DECLARE FUNCTION  thinBasic_Parse3Numbers               LIB "thinCore.DLL" ALIAS "thinBasic_Parse3Numbers"              (Num1 AS EXT, Num2 AS EXT, Num3 AS EXT) AS EXT
  DECLARE FUNCTION  thinBasic_Parse4Numbers               LIB "thinCore.DLL" ALIAS "thinBasic_Parse4Numbers"              (Num1 AS EXT, Num2 AS EXT, Num3 AS EXT, Num4 AS EXT) AS EXT
  DECLARE FUNCTION  thinBasic_Parse5Numbers               LIB "thinCore.DLL" ALIAS "thinBasic_Parse5Numbers"              (Num1 AS EXT, Num2 AS EXT, Num3 AS EXT, Num4 AS EXT, Num5 AS EXT) AS EXT
  DECLARE FUNCTION  thinBasic_Parse6Numbers               LIB "thinCore.DLL" ALIAS "thinBasic_Parse6Numbers"              (Num1 AS EXT, Num2 AS EXT, Num3 AS EXT, Num4 AS EXT, Num5 AS EXT, Num6 AS EXT) AS EXT
  DECLARE FUNCTION  thinBasic_Parse7Numbers               LIB "thinCore.DLL" ALIAS "thinBasic_Parse7Numbers"              (Num1 AS EXT, Num2 AS EXT, Num3 AS EXT, Num4 AS EXT, Num5 AS EXT, Num6 AS EXT, Num7 AS EXT) AS EXT
  '---

  DECLARE FUNCTION  thinBasic_Parse2Numbers1String        LIB "thinCore.DLL" ALIAS "thinBasic_Parse2Numbers1String"       (Num1 AS EXT, Num2 AS EXT, s1 AS STRING) AS EXT
  DECLARE FUNCTION  thinBasic_Parse3Numbers1String        LIB "thinCore.DLL" ALIAS "thinBasic_Parse3Numbers1String"       (Num1 AS EXT, Num2 AS EXT, Num3 AS EXT, s1 AS STRING) AS EXT
  '---

  DECLARE FUNCTION  thinBasic_ParseXNumbers               LIB "thinCore.DLL" _
                                                          ALIAS "thinBasic_ParseXNumbers" _
                                                          ( _
                                                            BYVAL MinNumToParse AS LONG, BYVAL MaxNumToParse AS LONG, _
                                                                      Num1  AS EXT    , _
                                                            OPTIONAL  Num2  AS EXT    , _
                                                                      Num3  AS EXT    , _
                                                                      Num4  AS EXT    , _
                                                                      Num5  AS EXT    , _
                                                                      Num6  AS EXT    , _
                                                                      Num7  AS EXT    , _
                                                                      Num8  AS EXT    , _
                                                                      Num9  AS EXT    , _
                                                                      Num10 AS EXT      _
                                                          ) AS EXT

  DECLARE FUNCTION  thinBasic_ParseXNumbersExt            LIB "thinCore.DLL" _
                                                          ALIAS "thinBasic_ParseXNumbersExt" _
                                                          ( _
                                                            BYVAL MinNumToParse AS LONG, BYVAL MaxNumToParse AS LONG, _
                                                                      Num1  AS EXT    , _
                                                            OPTIONAL  Num2  AS EXT    , _
                                                                      Num3  AS EXT    , _
                                                                      Num4  AS EXT    , _
                                                                      Num5  AS EXT    , _
                                                                      Num6  AS EXT    , _
                                                                      Num7  AS EXT    , _
                                                                      Num8  AS EXT    , _
                                                                      Num9  AS EXT    , _
                                                                      Num10 AS EXT    , _
                                                                      Num11 AS EXT    , _
                                                                      Num12 AS EXT    , _
                                                                      Num13 AS EXT    , _
                                                                      Num14 AS EXT    , _
                                                                      Num15 AS EXT      _
                                                          ) AS EXT
  '---
  DECLARE FUNCTION  thinBasic_Parse1StringXNumbers        LIB "thinCore.DLL" _
                                                          ALIAS "thinBasic_Parse1StringXNumbers" _
                                                          ( _
                                                            BYVAL MinNumToParse AS LONG, BYVAL MaxNumToParse AS LONG, _
                                                                      Str1  AS STRING , _
                                                                      Num1  AS EXT    , _
                                                            OPTIONAL  Num2  AS EXT    , _
                                                                      Num3  AS EXT    , _
                                                                      Num4  AS EXT    , _
                                                                      Num5  AS EXT    , _
                                                                      Num6  AS EXT    , _
                                                                      Num7  AS EXT    , _
                                                                      Num8  AS EXT    , _
                                                                      Num9  AS EXT    , _
                                                                      Num10 AS EXT      _
                                                          ) AS EXT

  '---
  DECLARE FUNCTION  thinBasic_Parse1String2Numbers        LIB "thinCore.DLL" _
                                                          ALIAS "thinBasic_Parse1String2Numbers" _
                                                          ( _
                                                                      Str1  AS STRING , _
                                                                      Num1  AS EXT    , _
                                                                      Num1  AS EXT      _
                                                          ) AS EXT

  '---
  ' Parse one string expression including possible "(" and ")" before and after the string
  ' This function is the equavalent of the numeric thinBasic_Parse1Number
  DECLARE FUNCTION  thinBasic_Parse1String                LIB "thinCore.DLL" ALIAS "thinBasic_Parse1String"               () AS STRING

  '---
  ' Parse one string expression. It also returns the numeric representation of the parsed string in case it represents a valid number
  DECLARE FUNCTION  thinBasic_ParseString                 LIB "thinCore.DLL" ALIAS "thinBasic_ParseString"                (BYREF sResult AS STRING) AS EXT

  '---
  ' Parse one string expression.
  DECLARE SUB       thinBasic_ParseStr                    LIB "thinCore.DLL" ALIAS "thinBasic_ParseStr"                   (BYREF sResult AS STRING)

  '---
  ' Parse a variant variable (scalar or array) and returns its pointer
  DECLARE FUNCTION  thinBasic_ParseVariant                LIB "thinCore.DLL" ALIAS "thinBasic_ParseVariant"               () AS DWORD


  DECLARE FUNCTION  thinBasic_CheckOpenParens             LIB "thinCore.DLL" ALIAS "thinBasic_CheckOpenParens"            (OPTIONAL BYVAL HideError AS LONG, BYVAL AutoPutBack AS LONG) AS LONG
  DECLARE FUNCTION  thinBasic_CheckOpenParens_Mandatory   LIB "thinCore.DLL" ALIAS "thinBasic_CheckOpenParens_Mandatory"  () AS LONG
  DECLARE FUNCTION  thinBasic_CheckOpenParens_Optional    LIB "thinCore.DLL" ALIAS "thinBasic_CheckOpenParens_Optional"   () AS LONG

  DECLARE FUNCTION  thinBasic_CheckCloseParens            LIB "thinCore.DLL" ALIAS "thinBasic_CheckCloseParens"           (OPTIONAL BYVAL HideError AS LONG, BYVAL AutoPutBack AS LONG) AS LONG
  DECLARE FUNCTION  thinBasic_CheckCloseParens_Mandatory  LIB "thinCore.DLL" ALIAS "thinBasic_CheckCloseParens_Mandatory" () AS LONG
  DECLARE FUNCTION  thinBasic_CheckCloseParens_Optional   LIB "thinCore.DLL" ALIAS "thinBasic_CheckCloseParens_Optional"  () AS LONG

  DECLARE FUNCTION  thinBasic_CheckComma                  LIB "thinCore.DLL" ALIAS "thinBasic_CheckComma"                 (OPTIONAL BYVAL HideError AS LONG, BYVAL AutoPutBack AS LONG) AS LONG
  DECLARE FUNCTION  thinBasic_CheckComma_Mandatory        LIB "thinCore.DLL" ALIAS "thinBasic_CheckComma_Mandatory"       () AS LONG
  DECLARE FUNCTION  thinBasic_CheckComma_Optional         LIB "thinCore.DLL" ALIAS "thinBasic_CheckComma_Optional"        () AS LONG

  DECLARE FUNCTION  thinBasic_CheckSemicolon_Mandatory    LIB "thinCore.DLL" ALIAS "thinBasic_CheckSemicolon_Mandatory"   () AS LONG
  DECLARE FUNCTION  thinBasic_CheckSemicolon_Optional     LIB "thinCore.DLL" ALIAS "thinBasic_CheckSemicolon_Optional"    () AS LONG

  DECLARE FUNCTION  thinBasic_CheckEqual_Mandatory        LIB "thinCore.DLL" ALIAS "thinBasic_CheckEqual_Mandatory"       () AS LONG
  DECLARE FUNCTION  thinBasic_CheckEqual_Optional         LIB "thinCore.DLL" ALIAS "thinBasic_CheckEqual_Optional"        () AS LONG

  DECLARE FUNCTION  thinBasic_CheckPoint_Mandatory        LIB "thinCore.DLL" ALIAS "thinBasic_CheckPoint_Mandatory"       () AS LONG
  DECLARE FUNCTION  thinBasic_CheckPoint_Optional         LIB "thinCore.DLL" ALIAS "thinBasic_CheckPoint_Optional"        () AS LONG

  DECLARE FUNCTION  thinBasic_CheckPlus_Optional          LIB "thinCore.DLL" ALIAS "thinBasic_CheckPlus_Optional"         () AS LONG
  DECLARE FUNCTION  thinBasic_CheckMinus_Optional         LIB "thinCore.DLL" ALIAS "thinBasic_CheckMinus_Optional"        () AS LONG
  DECLARE FUNCTION  thinBasic_CheckMult_Optional          LIB "thinCore.DLL" ALIAS "thinBasic_CheckMult_Optional"         () AS LONG
  DECLARE FUNCTION  thinBasic_CheckDiv_Optional           LIB "thinCore.DLL" ALIAS "thinBasic_CheckDiv_Optional"          () AS LONG

  DECLARE FUNCTION  thinBasic_CheckEOL_Optional           LIB "thinCore.DLL" ALIAS "thinBasic_CheckEOL_Optional"          () AS LONG


  DECLARE FUNCTION  thinBasic_GetUnknownToken             LIB "thinCore.DLL" ALIAS "thinBasic_GetUnknownToken"            (OPTIONAL BYVAL AutoPutBack AS LONG) AS STRING
  '----------------------------------------------------------------------------

  '----------------------------------------------------------------------------
  DECLARE FUNCTION  thinBasic_CheckEqualType_Mandatory    LIB "thinCore.DLL" ALIAS "thinBasic_CheckEqualType_Mandatory"   () AS LONG
    %Equal_EQ             = 1520&   ' =
    %Equal_PLUSEQUAL      = 1521&   ' +=
    %Equal_MINUSEQUAL     = 1522&   ' -=
    %Equal_MULTIPLYEQUAL  = 1523&   ' *=
    %Equal_DIVIDEEQUAL    = 1524&   ' /=
    %Equal_IDIVIDEEQUAL   = 1525&   ' \=
    %Equal_CONCEQUAL      = 1526&   ' &=
    %Equal_POINTEQUAL     = 1527&   ' .=
  '----------------------------------------------------------------------------

  '----------------------------------------------------------------------------
  DECLARE FUNCTION  thinBasic_DetermineType               LIB "thinCore.DLL" ALIAS "thinBasic_DetermineType"              () AS LONG
  '----------------------------------------------------------------------------
  ' Possible return values:
  '   %thinBasic_ReturnNumber
  '   %thinBasic_ReturnString
  '----------------------------------------------------------------------------

  '----------------------------------------------------------------------------
  'thinBasic_GetRunTimeInfo
  '----------------------------------------------------------------------------
  ' The following information can be taken:
  '  "SCRIPT_PATH"  Path to script
  '  "APP_PATH"     Path to thinBasic
  '  "HWND"         Handle to main thinBasic window
  '----------------------------------------------------------------------------
  DECLARE FUNCTION  thinBasic_GetRunTimeInfo    LIB "thinCore.DLL" ALIAS "thinBasic_GetRunTimeInfo"   (BYVAL InfoName AS STRING) AS STRING
  '----------------------------------------------------------------------------

  '----------------------------------------------------------------------------
  'thinBasic_ScriptIsObuscated
  '----------------------------------------------------------------------------
  '----------------------------------------------------------------------------
  DECLARE FUNCTION  thinBasic_ScriptIsObfuscated    LIB "thinCore.DLL" ALIAS "thinBasic_ScriptIsObfuscated"   () AS LONG
  '----------------------------------------------------------------------------


  '----------------------------------------------------------------------------
  'Trace Handling
  '----------------------------------------------------------------------------
  '----------------------------------------------------------------------------
  ' TRACE Equates
    '---What to ask for
      %TRACE_What_SourcePtr                       =   1&
      %TRACE_What_StackLevel                      =  10&
      %TRACE_What_IFLevel                         =  20&
      %TRACE_What_SourceFullPath                  =  30&

    '---Error codes
      %TRACE_Error_NotPossible_Obfuscated         =   1&

      %TRACE_Error_InstallHandle_Null             = 200&
      %TRACE_Error_InstallHandle_AlreadyInstalled = 201&

  '----------------------------------------------------------------------------
  'thinBasic_ITrace_GetValue
  '----------------------------------------------------------------------------
  '
  '
  '
  '
  '----------------------------------------------------------------------------
    DECLARE FUNCTION thinBasic_ITrace_GetValue                      _
                            LIB   "thinCore.dll"                    _
                            ALIAS "thinBasic_ITrace_GetValue"       _
                            (                                       _
                                        BYVAL lWhat AS LONG       , _
                              OPTIONAL  BYVAL sWhat AS STRING     , _
                                        BYVAL lRet1 AS LONG PTR   , _
                                        BYVAL lRet2 AS LONG PTR   , _
                                        BYVAL sRet1 AS STRING PTR   _
                            ) AS LONG

  '----------------------------------------------------------------------------
  'thinBasic_ITrace_InstallHandle
  '----------------------------------------------------------------------------
  '
  '
  '
  '
  '----------------------------------------------------------------------------
    DECLARE FUNCTION thinBasic_ITrace_InstallHandle                 _
                            LIB   "thinCore.dll"                    _
                            ALIAS "thinBasic_ITrace_InstallHandle"  _
                            (                                       _
                                        BYVAL fHandle AS LONG       _
                            ) AS LONG
  '----------------------------------------------------------------------------

  '----------------------------------------------------------------------------
  'thinBasic_StackGetCurrent
  '----------------------------------------------------------------------------
  ' Returns the current script stack level.
  ' 1 = Global, 2 = next function executed, 3 = ...
  '----------------------------------------------------------------------------
    DECLARE FUNCTION thinBasic_StackGetCurrent                      _
                            LIB   "thinCore.dll"                    _
                            ALIAS "thinBasic_StackGetCurrent"       _
                            (                                       _
                            ) AS LONG
  '------------------------------------------------------------------------------

  '----------------------------------------------------------------------------
  'thinBasic_StackGetList
  '----------------------------------------------------------------------------
  ' Returns a string containing the names of the current nesting stack levels
  ' As a minimum this function will return one string containing "GLOBAL"
  '----------------------------------------------------------------------------
    DECLARE FUNCTION thinBasic_StackGetList                         _
                            LIB   "thinCore.dll"                    _
                            ALIAS "thinBasic_StackGetList"          _
                            (                                       _
                              OPTIONAL BYVAL sSep AS STRING         _
                            ) AS STRING
  '----------------------------------------------------------------------------

  '----------------------------------------------------------------------------
  'ERROR Handling
  '----------------------------------------------------------------------------

  '----------------------------------------------------------------------------
  'thinBasic_GetLastError
  '----------------------------------------------------------------------------
  ' Returns the last occurred error code
  '----------------------------------------------------------------------------
  DECLARE FUNCTION  thinBasic_GetLastError      LIB "thinCore.DLL" ALIAS "thinBasic_GetLastError"        () AS LONG

  '----------------------------------------------------------------------------
  'thinBasic_ErrorFlag
  '----------------------------------------------------------------------------
  ' Returns a value different from 0 if a runtime error occurred
  '----------------------------------------------------------------------------
  DECLARE FUNCTION  thinBasic_ErrorFlag         LIB "thinCore.DLL" ALIAS "thinBasic_ErrorFlag"        () AS LONG

  '----------------------------------------------------------------------------
  'thinBasic_ErrorFree
  '----------------------------------------------------------------------------
  ' Returns -1 if there thinBasic is not under runtime error state
  '----------------------------------------------------------------------------
  DECLARE FUNCTION  thinBasic_ErrorFree         LIB "thinCore.DLL" ALIAS "thinBasic_ErrorFree"        () AS LONG
  '----------------------------------------------------------------------------

  '----------------------------------------------------------------------------
  'thinBasic_ErrorUserConfirmed
  '----------------------------------------------------------------------------
  ' Returns -1 if, after an error, user has confirmed the dialog
  '----------------------------------------------------------------------------
  DECLARE FUNCTION  thinBasic_ErrorUserConfirmed         LIB "thinCore.DLL" ALIAS "thinBasic_ErrorUserConfirmed"        () AS LONG
  '----------------------------------------------------------------------------

  '----------------------------------------------------------------------------
  'thinBasic_RunTimeError
  '----------------------------------------------------------------------------
  ' Use internal thinCore engine to generate a runtime error
  '  ErrorCode      Error code. Get one from the below list
  '  AdditionalInfo Personalized text to be shown into runtime error dialog
  '----------------------------------------------------------------------------
  DECLARE FUNCTION thinBasic_RunTimeError                               _
                          LIB "thinCore.dll"                            _
                          ALIAS "thinBasic_RunTimeError"                _
                          ( _
                                      BYVAL ErrorCode       AS LONG   , _
                             OPTIONAL BYVAL AdditionalInfo  AS STRING   _
                          ) AS LONG

  '----------------------------------------------------------------------------
  'thinBasic_GetControllingLevels
  '----------------------------------------------------------------------------
  ' Return current nidification levels of commonly used flow controlling keywords
  ' All parameters are LONGs passed BYREF and are used to get back levels
  ' from thinBasic Core Engine
  '----------------------------------------------------------------------------
  DECLARE FUNCTION thinBasic_GetControllingLevels                       _
                          LIB "thinCore.dll"                            _
                          ALIAS "thinBasic_GetControllingLevels"        _
                          ( _
                                      BYREF Level_If     AS LONG      , _
                                      BYREF Level_Select AS LONG      , _
                                      BYREF Level_For    AS LONG      , _
                                      BYREF Level_While  AS LONG      , _
                                      BYREF Level_Do     AS LONG        _
                           ) AS LONG

  '------------------------------------------------------------------------------
  ' RunTime Errors Codes
  '------------------------------------------------------------------------------
  %ERR__PARENS                                =   1&
  %ERR__NOEXP                                 =   2&
  %ERR__DIV_ZERO                              =   3&
  %ERR__EQUAL_EXP                             =   4&
  %ERR__NOT_VAR                               =   5&
  %ERR__LAB_TAB_FULL                          =   6&
  %ERR__DUP_LAB                               =   7&
  %ERR__UNDEF_LAB                             =   8&
  %ERR__THEN_EXPECTED                         =   9&
  %ERR__TO_EXPECTED                           =  10&
  %ERR__TOO_MANY_FOR                          =  11&
  %ERR__NEXT_WITHOUT_FOR                      =  12&
  %ERR__MISSING_SEMICOLON                     =  13&

  %ERR__COMMAND_RET_NONE_IN_EXPRESSION        =  14&

  %ERR__MISS_QUOTE                            =  15&
  %ERR__BAD_FILE                              =  16&
  %ERR__STR_EXPECTED                          =  17&
  %ERR__UNKNOWN_KEYWORD                       =  18&
  %ERR__MISSING_OPENPARENS                    =  19&
  %ERR__MISSING_CLOSEPARENS                   =  20&
  %ERR__MISSING_COMMA                         =  21&
  %ERR__MISSING_SQUARECLOSEPARENS             =  22&

  %ERR__EOL_INCORRECT                         =  23&

  %ERR__DOUBLE_CONCATENATION                  =  24&
  %ERR__COMMAND_UNKNOWN_RETURNED_PARAMETER    =  25&
  %ERR__PRIMITIVE_STR                         =  26&
  %ERR__PRIMITIVE_NUM                         =  27&
  %ERR__PRINT_ERROR                           =  28&
  %ERR__PRINT_ERROR_NOENDOFLINE               =  29&
  %ERR__VARIABLE_NOT_DEFINED                  =  30&
  %ERR__ATOM_TOKEN_TYPE_NUMERIC               =  31&
  %ERR__ATOM_NUM                              =  31&  '---Used as an abbreviation in macros
  %ERR__IF_WITHOUT_ENDIF                      =  32&
  %ERR__IF_ENDIF_WITHOUT_IF                   =  33&
  %ERR__TOO_MANY_WHILE                        =  34&
  %ERR__WHILE_WITHOUT_WEND                    =  35&
  %ERR__DIM_TYPE_NOT_DEFINED                  =  36&
  %ERR__EXIT_NO_KEY_FOUND                     =  37&
  %ERR__NO_END_FUNCTION_FOUND                 =  38&
  %ERR__FUNCTION_NAME_DUPLICATE               =  39&
  %ERR__FUNCTION_NAME_IS_KEY                  =  40&
  %ERR__FUNCTION_NAME_IS_VAR                  =  41&
  %ERR__FUNCTION_NAME_IS_UDT                  =  42&
  %ERR__END_NO_KEY_FOUND                      =  43&

  %ERR__DIM_MISSING_AS                        =  44&
  %ERR__UNDEFINED_TOKEN                       =  45&
  %ERR__UNSUPPORTED_CHAR                      =  46&

  %ERR__FUNCTION_DECLARE_MISSING_AS           =  47&
  %ERR__DECLARE_FUNCTION_OR_SUB_EXPECTED      =  48&

  %ERR__DOLOOP_WRONG_CONDITION                =  49&

  %ERR__MISSING_ALIAS                         =  50&
  %ERR__MISSING_LIB                           =  51&
  %ERR__UNDEFINED_VAR_TYPE                    =  52&
  %ERR__PARAMETER_BYREF_INCORRECT_PTR         =  53&

  %ERR__LOOP_EXPECTED_WHILE_OR_UNTIL          =  55&

  %ERR__END_FUNCTION_WITHOUT_FUNCTION         =  58&
  %ERR__END_FUNCTION_FOUND                    =  59&

  %ERR__ITERATE_NO_KEY_FOUND                  =  60&

  %ERR__WITH_ENDWITH_ERROR                    =  64&

  %ERR__TOO_NESTED_DOLOOP                     =  65&
  %ERR__DOLOOP_MISSING_DO_OR_LOOP             =  66&

  %ERR__VARIABLE_NOT_DIMENSIONED              =  70&
  %ERR__VARIABLE_ISNOT_ARRAY                  =  71&
  %ERR__VARIABLE_MUSTBE_STRING_TYPE           =  72&

  %ERR__REDIM_NEW_TYPE_NOT_SUPPORTED          =  73&
  %ERR__REDIM_PRESERVE_NOTVALID_ABSOLUTE      =  74&

  %ERR__VARIABLE_MUSTBE_UDT_TYPE              =  75&

  %ERR__KEYWORD_NOT_EXPECTED                  =  76&
  %ERR__TOKEN_NOT_EXPECTED                    =  77&

  %ERR__INCLUDE_FILE_NOT_FOUND                =  80&

  %ERR__DIM_UNEXPECTED_KEYWORD                =  85&

  %ERR__FUNCTION_NOT_SUPPORTED                =  90&

  %ERR__ARRAY_FUNCTION_NOT_SUPPORTED          =  91&

  %ERR__UDT_ELEMENT_NOT_FOUND                 = 100&
  %ERR__UDT_EXPECTED                          = 101&
  %ERR__UDT_EQU_OR_ELEMENT_EXPECTED           = 102&

  %ERR__ASSIGNMENT_NOT_SUPPORTED              = 110&

  %ERR__RELATIONAL_EXPECTED                   = 115&

  %ERR__API_LIB_NOT_FOUND                     = 120&
  %ERR__API_FUNCTION_NOT_FOUND_IN_LIB         = 121&
  %ERR__API_GENERAL_ADDRESS_NOT_PRESENT       = 122&

  %ERR__CALL_NOTSUPPORTEDSTATEMENT            = 130&
  %ERR__CALL_FUNCTIONNOTFOUND                 = 131&

  %ERR__FUNCTIONNOTFOUND                      = 133&
  %ERR__FUNCTION_EXPECTED_CALLBACK            = 134&

  %ERR__EQUATE_ALREADY_DEFINED                = 135&
  %ERR__EQUATE_ALREADY_DEFINED_DIFFERENT      = 136&

  %ERR__VARIABLE_NAME_DUPLICATE_GLOBAL        = 142&
  %ERR__VARIABLE_NAME_DUPLICATE_FUNCTION      = 144&
  %ERR__VARIABLE_NAME_DUPLICATE_LOCAL         = 145&
  %ERR__VARIABLE_NAME_DUPLICATE               = 146&

  %ERR__FOR_StepShouldBeNegative              = 150&
  %ERR__FOR_StepShouldBePositive              = 151&
  %ERR__FOR_ExpectedAVariable                 = 152&
  %ERR__FOR_StepIsZero                        = 153&
  %ERR__FOR_VarMustBeNumeric                  = 154&

  %ERR__ALIAS_CommandNameExpected             = 160&
  %ERR__ALIAS_AsExpected                      = 161&
  %ERR__ALIAS_UndefNotUndef                   = 162&

  %ERR__TYPE_MISSING_END_UNION                = 169&
  %ERR__TYPE_MISSING_END_TYPE                 = 170&
  %ERR__TYPE_MISSING_END_CLASS                = 171&
  %ERR__TYPE_TYPE_NOT_DEFINED                 = 172&
  %ERR__TYPE_MISSING_AS                       = 173&
  %ERR__TYPE_NAME_MUSTBE_UNDEFINED            = 174&
  %ERR__TYPE_ARRAY_MUSTBE_DIMENSIONED         = 175&
  %ERR__TYPE_STRINGS_MUST_HAVE_SIZE           = 176&
  %ERR__TYPE_ELEMENT_ALREADY_PRESENT          = 177&
  %ERR__TYPE_ELEMENT_ALREADY_PRESENT_INHERIT  = 178&
  %ERR__TYPE_DYNSTRING_INSIDE_UNION           = 179&

  %ERR__NO_END_RAWTEXT_FOUND                  = 180&

  %ERR__BEGIN_BLOCK_UNSUPORTED                = 190&
  %ERR__BEGIN_CONST_MISSING_END               = 191&

  %ERR__FUNCTION_PARAM_UNRECOGNIZED_TYPE      = 220&

  %ERR__DO_WITHOUT_LOOP                       = 245&
  %ERR__FUNCTION_MISSING_AS                   = 246&
  %ERR__REGEXPR_MISSING_TO                    = 247&
  %ERR__REGEXPR_MISSING_IN                    = 248&
  %ERR__SELECT_WITHOUT_ENDSELECT              = 249&
  %ERR__DUPLICATE_SYMBOL                      = 250&
  %ERR__INVALIDNUMERICCHAR                    = 251&
  %ERR__INVALIDDELIMITER                      = 252&
  %ERR__INVALIDDATATYPE                       = 253&
  %ERR__VARIABLE_EXPECTED                     = 254&
  %ERR__VARIABLE_VARIANT_EXPECTED             = 255&

  %ERR__SELECT_MISSING_CASE                   = 270&
  %ERR__SELECT_ERROR_KINDOF_OPERATION         = 271&
  %ERR__SELECT_CODE_BETWEEN_SELECT_CASE       = 272&

  %ERR__STRPTR_VARIABLE_NOT_A_DYNSTRING_NUM   = 280&
  %ERR__STRPTR_VARIABLE_NOT_A_DYNSTRING_VAR   = 281&
  %ERR__STRPTR_VARIABLE_NOT_A_DYNSTRING_UDT   = 282&

  %ERR__APICALL_REF_EXPECTED                  = 300&

  %ERR__ARRAY_OUT_OF_BOUND                    = 400&

  %ERR__MODULE_SPECIFIC                       = 500&

  %ERR__PREPARSER_DirectiveNotSupported       = 800&

  %ERR__PREPARSER_ScriptVersionRequest        = 820&

  %ERR__INTERNAL_RETURNMAINTYPE               = 900&

  %ERR__INTERNAL_DECRIPTION                   = 910&

  %ERR__INTERNAL_UDTBUFFER_SHORT              = 915&

  %ERR__INTERNAL_RETURNNONE_NOCODEPTR         = 921&
  %ERR__INTERNAL_RETURNNUMBER_NOCODEPTR       = 922&
  %ERR__INTERNAL_RETURNSTRING_NOCODEPTR       = 923&

  %ERR__CLASS_NEW_NOINDEXALLOWED              = 5010&
  %ERR__CLASS_NEW_DIFFERENTCLASS              = 5015&
  %ERR__CLASS_NEW_NOCLASS                     = 5020&
  %ERR__CLASS_NEW_EXPECTED_NEW                = 5025&
  %ERR__CLASS_NOT_INIT_WITH_NEW               = 5030&
  %ERR__CLASS_SET_NOW_ALLOWED                 = 5035&

  %ERR__CLASS_METHODPROPERTY_NOTFOUND         = 5100&
  %ERR__CLASS_EXPECTED                        = 5110&

  %ERR__TRACE_STOP_BY_USER                    = 11000&

  %ERR__OBFUSCATION_FILENOTVALID              = 12000&

  %ERR__COM_GENERIC                           = 30000&



  '----------------------------------------------------------------------------
  'thinBasic_Class_Add
  '----------------------------------------------------------------------------
  ' Add a new class to thinBasic Core Engine
  '----------------------------------------------------------------------------
    DECLARE FUNCTION thinBasic_Class_Add                                _
                            LIB   "thinCore.dll"                        _
                            ALIAS "thinBasic_Class_Add"                 _
                            (                                           _
                                BYVAL sClassName            AS STRING , _     '---Name of the Class to be created
                                BYVAL pClassFunc            AS LONG     _     '---Pointer to a class function that will handle calls to methods
                            ) AS LONG
  '----------------------------------------------------------------------------

  '----------------------------------------------------------------------------
  'thinBasic_Class_AddMethod
  '----------------------------------------------------------------------------
  ' Add a method to a class previously created with thinBasic_Class_Add
  '----------------------------------------------------------------------------
    DECLARE FUNCTION thinBasic_Class_AddMethod                          _
                            LIB   "thinCore.dll"                        _
                            ALIAS "thinBasic_Class_AddMethod"           _
                            (                                           _
                                BYVAL pClass                AS LONG   , _     '---Poiter to a class. This is the value returned by thinBasic_Class_Add
                                BYVAL sMethodName           AS STRING , _     '---Name of the Class to be created
                                BYVAL MethodReturnType      AS LONG   , _
                                BYVAL pMethodFunc           AS LONG     _     '---Pointer to a method function that will handle method execution
                            ) AS LONG
  '----------------------------------------------------------------------------

  '----------------------------------------------------------------------------
  'thinBasic_ParseClass
  '----------------------------------------------------------------------------
  ' Return pointer to a class. Use it to map your internal module class
  '----------------------------------------------------------------------------
    DECLARE FUNCTION thinBasic_ParseClass                               _
                            LIB   "thinCore.dll"                        _
                            ALIAS "thinBasic_ParseClass"                _
                            (                                           _
                            ) AS LONG
  '----------------------------------------------------------------------------

  %Class_Action_None          = 0?
  %Class_Action_Get           = 1?
  %Class_Action_Set           = 2?

  %Class_Action_Constructor   = 100?
  %Class_Action_Destructor    = 110?

  '----------------------------------------------------------------------------
  'thinBasic_Class_AddProperty
  '----------------------------------------------------------------------------
  ' Add a property to a class previously created with thinBasic_Class_Add
  '----------------------------------------------------------------------------
    DECLARE FUNCTION thinBasic_Class_AddProperty  _
                            LIB   "thinCore.dll"                        _
                            ALIAS "thinBasic_Class_AddProperty"         _
                            (                                           _
                                BYVAL pClass                AS LONG   , _     '---Poiter to a class. This is the value returned by thinBasic_Class_Add
                                BYVAL sPropertyName         AS STRING , _     '---Name of the Class to be created
                                BYVAL PropertyReturnType    AS LONG   , _
                                BYVAL PtrToPropertyFunction AS LONG     _     '---Pointer to a method function that will handle method execution
                             ) AS LONG


  '----------------------------------------------------------------------------
  'thinBasic_IsBundled
  '----------------------------------------------------------------------------
  ' %TRUE if current execution is started from a bundled executable
  '----------------------------------------------------------------------------
  DECLARE FUNCTION thinBasic_IsBundled                                  _
                            LIB   "thinCore.dll"                        _
                            ALIAS "thinBasic_IsBundled"                 _
                            (                                           _
                            ) AS LONG

  '----------------------------------------------------------------------------
  'thinBasic_IsIsolated
  '----------------------------------------------------------------------------
  ' %TRUE if current execution is started from a bundled executable and
  ' isolation mode is taking place. In isolation mode all modules/dlls are
  ' extracted into a temp directory created at script runtime and
  ' destroyed when script stop execution
  '----------------------------------------------------------------------------
  ' If script is bundled also Isoaltion is %TRUE
  ' In future maybe execution of script and extraction of modules will
  ' take place directly from memory
  '----------------------------------------------------------------------------
  DECLARE FUNCTION thinBasic_IsIsolated                                 _
                            LIB   "thinCore.dll"                        _
                            ALIAS "thinBasic_IsIsolated"                _
                            (                                           _
                            ) AS LONG

  '----------------------------------------------------------------------------
  'thinBasic_IsolationPath
  '----------------------------------------------------------------------------
  ' Returns isoaltion path. See thinBasic_IsIsolated
  '----------------------------------------------------------------------------
  DECLARE FUNCTION thinBasic_IsolationPath                              _
                            LIB   "thinCore.dll"                        _
                            ALIAS "thinBasic_IsolationPath"             _
                            (                                           _
                            ) AS STRING
