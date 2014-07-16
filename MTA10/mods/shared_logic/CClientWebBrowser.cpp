/*****************************************************************************
*
*  PROJECT:     Multi Theft Auto v1.0
*               (Shared logic for modifications)
*  LICENSE:     See LICENSE in the top level directory
*  FILE:        mods/shared_logic/CClientWebBrowser.cpp
*  PURPOSE:     ClientEntity webbrowser tab class
*
*****************************************************************************/

#include "StdInc.h"
#include "CClientWebBrowser.h"

CClientWebBrowser::CClientWebBrowser ( CClientManager* pManager, ElementID ID, CWebBrowserItem* pWebBrowserItem, CWebViewInterface* pWebView )
    : ClassInit ( this ), CClientTexture ( pManager, ID, pWebBrowserItem ), m_pWebView ( pWebView )
{
    // Set events interface
    m_pWebView->SetWebBrowserEvents ( this );
}

CClientWebBrowser::~CClientWebBrowser ()
{
    // We can't release the memory here since we deal with an interface
    m_pWebView = NULL;

    // Unlink from tree
    Unlink ();
}

bool CClientWebBrowser::IsLoading ()
{
    return m_pWebView->IsLoading ();
}

bool CClientWebBrowser::LoadURL ( const SString& strURL, bool bFilterEnabled )
{
    return m_pWebView->LoadURL ( strURL, bFilterEnabled );
}

void CClientWebBrowser::GetTitle ( SString& outPageTitle )
{
    m_pWebView->GetTitle ( outPageTitle );
}

void CClientWebBrowser::GetURL ( SString& outURL )
{
    m_pWebView->GetURL ( outURL );
}

void CClientWebBrowser::SetRenderingPaused ( bool bPaused )
{
    m_pWebView->SetRenderingPaused ( bPaused );
}

void CClientWebBrowser::SetTransparent ( bool bTransparent )
{
    m_pWebView->SetTransparent ( bTransparent );
}

bool CClientWebBrowser::ExecuteJavascript ( const SString& strJavascriptCode )
{
    // Don't allow javascript code execution on remote websites
    if ( !m_pWebView->IsLocal () )
        return false;

    m_pWebView->ExecuteJavascript ( strJavascriptCode );
    return true;
}

void CClientWebBrowser::InjectMouseMove ( int iPosX, int iPosY )
{
    m_pWebView->InjectMouseMove ( iPosX, iPosY );
}

void CClientWebBrowser::InjectMouseDown ( int mouseButton )
{
    m_pWebView->InjectMouseDown ( mouseButton );
}

void CClientWebBrowser::InjectMouseUp ( int mouseButton )
{
    m_pWebView->InjectMouseUp ( mouseButton );
}

void CClientWebBrowser::InjectMouseWheel ( int iScrollVert, int iScrollHorz )
{
    m_pWebView->InjectMouseWheel ( iScrollVert, iScrollHorz );
}

void CClientWebBrowser::InjectKeyboardEvent ( const SString& strKey, bool bKeyDown, bool bCharacter )
{
    m_pWebView->InjectKeyboardEvent ( strKey, bKeyDown, bCharacter );
}

bool CClientWebBrowser::IsLocal ()
{
    return m_pWebView->IsLocal ();
}

void CClientWebBrowser::SetTempURL ( const SString& strTempURL )
{
    m_pWebView->SetTempURL ( strTempURL );
}

bool CClientWebBrowser::SetAudioVolume ( float fVolume )
{
    return m_pWebView->SetAudioVolume ( fVolume );
}

////////////////////////////////////////////////////////////////////////////
//                                                                        //
//            CWebBrowserEventsInterface implementation                   //
//                                                                        //
////////////////////////////////////////////////////////////////////////////
void CClientWebBrowser::Events_OnDocumentReady ( const SString& strURL )
{
    CLuaArguments Arguments;
    Arguments.PushString ( strURL );
    CallEvent ( "onClientBrowserDocumentReady", Arguments, false );
}

void CClientWebBrowser::Events_OnLoadingFailed ( const SString& strURL, int errorCode, const SString& errorDescription )
{
    CLuaArguments Arguments;
    Arguments.PushString ( strURL );
    Arguments.PushNumber ( errorCode );
    Arguments.PushString ( errorDescription );
    CallEvent ( "onClientBrowserLoadingFailed", Arguments, false );
}

void CClientWebBrowser::Events_OnNavigate ( const SString& strURL, bool bMainFrame )
{
    CLuaArguments Arguments;
    Arguments.PushString ( strURL );
    Arguments.PushBoolean ( bMainFrame );
    CallEvent ( "onClientBrowserNavigate", Arguments, false );
}

void CClientWebBrowser::Events_OnPopup ( const SString& strTargetURL, const SString& strOpenerURL, bool bPopup )
{
    CLuaArguments Arguments;
    Arguments.PushString ( strTargetURL );
    Arguments.PushString ( strOpenerURL );
    Arguments.PushBoolean ( bPopup );
    CallEvent ( "onClientBrowserPopup", Arguments, false );
}