//------------------------------------------------------------------------
// $Id: AcsApp/AcsApp/CSingletonTemplate.h 1.1 2019/10/08 13:02:07CEST Allgemeiner Benutzer bei TKE (tke2) Exp  $
//------------------------------------------------------------------------

#ifndef __CSingletonTemplate_H__
#define __CSingletonTemplate_H__

template <class T> class CSingletonTemplate
{
  //------------------------------------------------------------------------
  // KONSTANT, ENUM, STRUCT DECLARATIONS
  //------------------------------------------------------------------------
public:
protected:
private:

  //------------------------------------------------------------------------
  // MEMBER DECLARATIONS
  //------------------------------------------------------------------------
public:
protected:
private:
  static T* m_Instance;

  //------------------------------------------------------------------------
  // FUNCTION DECLARATIONS
  //------------------------------------------------------------------------
public:
  static T* GetInstance()
  {
    if (m_Instance == 0)
    {
      m_Instance = new T();
    }
    return m_Instance;
  }

  static T& GetRefInstance()
  {
    if (m_Instance == 0)
    {
      m_Instance = new T();
    }
    return *m_Instance;
  }

  static void Release()
  {
    if (m_Instance != 0)
    {
      delete m_Instance;
      m_Instance = 0;
    }
  }

protected:
  CSingletonTemplate() { ; };                                       // Hidden constructor
  CSingletonTemplate(CSingletonTemplate const&) { ; };              // Hidden copy constructor
  CSingletonTemplate& operator=(CSingletonTemplate const&) { ; };   // Hidden assign operation
  ~CSingletonTemplate() { ; };                                      // Hidden destructor

private:

};

template <class T>  T* CSingletonTemplate<T>::m_Instance = 0;


#endif // __CSingletonTemplate_H__