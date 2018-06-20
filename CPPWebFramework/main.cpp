#include <QtTest>
#include <tests/tst_configuration.h>
#include <tests/tst_cppwebapplication.h>
#include <tests/tst_cppwebserver.h>
#include <tests/tst_cppwebcontroller.h>
#include <tests/tst_cstlcompiler.h>
#include <tests/tst_cstlcompilerattributes.h>
#include <tests/tst_cstlcompilerfor.h>
#include <tests/tst_cstlcompilerif.h>
#include <tests/tst_cstlcompilerimport.h>
#include <tests/tst_cstlcompilerobject.h>
#include <tests/tst_filemanager.h>
#include <tests/tst_filter.h>
#include <tests/tst_filterchain.h>
#include <tests/tst_httpparser.h>
#include <tests/tst_httpreadrequest.h>
#include <tests/tst_request.h>
#include <tests/tst_response.h>
#include <tests/tst_session.h>
#include <tests/tst_metaclassparser.h>
#include <tests/tst_properties.h>
#include <tests/tst_qlistobject.h>
#include <tests/tst_qmapthreadsafety.h>
#include <tests/tst_requestdispatcher.h>
#include <tests/tst_cstlcompilerout.h>
#include <tests/tst_urlencoder.h>


int main(int argc, char** argv)
{
   int status = 0;
   auto ASSERT_TEST = [&status, argc, argv](QObject* obj) { status |= QTest::qExec(obj, argc, argv); delete obj; };

   ASSERT_TEST(new TST_Configuration);
   ASSERT_TEST(new TST_CppWebApplication);
   ASSERT_TEST(new TST_CppWebServer);
   ASSERT_TEST(new TST_CppWebController);
   ASSERT_TEST(new TST_CSTLCompiler);
   ASSERT_TEST(new TST_CSTLCompilerAttributes);
   ASSERT_TEST(new TST_CSTLCompilerFor);
   ASSERT_TEST(new TST_CSTLCompilerIf);
   ASSERT_TEST(new TST_CSTLCompilerImport);
   ASSERT_TEST(new TST_CSTLCompilerObject);
   ASSERT_TEST(new TST_FileManager);
   ASSERT_TEST(new TST_Filter);
   ASSERT_TEST(new TST_FilterChain);
   ASSERT_TEST(new TST_HttpParser);
   ASSERT_TEST(new TST_HttpReadRequest);
   ASSERT_TEST(new TST_Request);
   ASSERT_TEST(new TST_Response);
   ASSERT_TEST(new TST_Session);
   ASSERT_TEST(new TST_MetaClassParser);
   ASSERT_TEST(new TST_Properties);
   ASSERT_TEST(new TST_QListObject);
   ASSERT_TEST(new TST_QMapThreadSafety);
   ASSERT_TEST(new TST_RequestDispatcher);
   ASSERT_TEST(new TST_URLEncoder);
   ASSERT_TEST(new TST_CSTLCompilerOut);

   return status;
}
