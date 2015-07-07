/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 3.0.2
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

namespace FontGenerator.swig {

unsafe partial class DLL : global::System.IDisposable {
  private global::System.Runtime.InteropServices.HandleRef swigCPtr;
  protected bool swigCMemOwn;

  internal DLL(global::System.IntPtr cPtr, bool cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = new global::System.Runtime.InteropServices.HandleRef(this, cPtr);
  }

  internal static global::System.Runtime.InteropServices.HandleRef getCPtr(DLL obj) {
    return (obj == null) ? new global::System.Runtime.InteropServices.HandleRef(null, global::System.IntPtr.Zero) : obj.swigCPtr;
  }

  ~DLL() {
    Dispose();
  }

  public virtual void Dispose() {
    lock(this) {
      if (swigCPtr.Handle != global::System.IntPtr.Zero) {
        if (swigCMemOwn) {
          swigCMemOwn = false;
          FontGeneratorPINVOKE.delete_DLL(swigCPtr);
        }
        swigCPtr = new global::System.Runtime.InteropServices.HandleRef(null, global::System.IntPtr.Zero);
      }
      global::System.GC.SuppressFinalize(this);
    }
  }

  public DLL() : this(FontGeneratorPINVOKE.new_DLL(), true) {
  }

  public void LoadFontNames() {
    FontGeneratorPINVOKE.DLL_LoadFontNames(swigCPtr);
  }

  public int GetFontCount() {
    int ret = FontGeneratorPINVOKE.DLL_GetFontCount(swigCPtr);
    return ret;
  }

  public string GetFontName(int index) {
    string ret = System.Runtime.InteropServices.Marshal.PtrToStringUni(FontGeneratorPINVOKE.DLL_GetFontName(swigCPtr, index));
    return ret;
  }

  public string GetFontPath(int index) {
    string ret = System.Runtime.InteropServices.Marshal.PtrToStringUni(FontGeneratorPINVOKE.DLL_GetFontPath(swigCPtr, index));
    return ret;
  }

  public string SavePreview() {
    string ret = System.Runtime.InteropServices.Marshal.PtrToStringUni(FontGeneratorPINVOKE.DLL_SavePreview(swigCPtr));
    return ret;
  }

  public bool Run() {
    bool ret = FontGeneratorPINVOKE.DLL_Run(swigCPtr);
    return ret;
  }

  public void SetFontSize(int fontSize) {
    FontGeneratorPINVOKE.DLL_SetFontSize(swigCPtr, fontSize);
  }

  public void SetFontColor(byte r, byte g, byte b, byte a) {
    FontGeneratorPINVOKE.DLL_SetFontColor(swigCPtr, r, g, b, a);
  }

  public void SetFontName(string name) {
    FontGeneratorPINVOKE.DLL_SetFontName(swigCPtr, name);
  }

  public void SetTextFilePath(string path) {
    FontGeneratorPINVOKE.DLL_SetTextFilePath(swigCPtr, path);
  }

  public void SetExportPath(string path) {
    FontGeneratorPINVOKE.DLL_SetExportPath(swigCPtr, path);
  }

  public void SetSheetSize(int sheetSize) {
    FontGeneratorPINVOKE.DLL_SetSheetSize(swigCPtr, sheetSize);
  }

  public void SetOutlineColor(byte r, byte g, byte b, byte a) {
    FontGeneratorPINVOKE.DLL_SetOutlineColor(swigCPtr, r, g, b, a);
  }

  public void SetOutlineSize(int size) {
    FontGeneratorPINVOKE.DLL_SetOutlineSize(swigCPtr, size);
  }

  public void SetOutlineSampling(int sampling) {
    FontGeneratorPINVOKE.DLL_SetOutlineSampling(swigCPtr, sampling);
  }

}

}
