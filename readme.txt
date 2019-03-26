
$ git status
On branch master
Your branch is up to date with 'origin/master'.

Changes not staged for commit:
  (use "git add <file>..." to update what will be committed)
  (use "git checkout -- <file>..." to discard changes in working directory)

        modified:   include/OgreOggStreamBufferSound.h


$ git diff include/OgreOggStreamBufferSound.h
diff --git a/include/OgreOggStreamBufferSound.h b/include/OgreOggStreamBufferSound.h
index 0e96c0c..27d32fd 100644
--- a/include/OgreOggStreamBufferSound.h
+++ b/include/OgreOggStreamBufferSound.h
@@ -136,7 +136,7 @@ namespace OgreOggSound
                        Calculates a block aligned buffer size of 250ms using
                        sounds properties
                 */
-               bool _queryBufferInfo() {}
+               bool _queryBufferInfo() { return true; }^M
                /** Releases buffers and OpenAL objects.
                @remarks
                        Cleans up this sounds OpenAL objects, including buffer



预处理器定义OGGSOUND_EXPORT宏

编译完ogre-oggsound插件后，连接库及头文件install至ogre sdk