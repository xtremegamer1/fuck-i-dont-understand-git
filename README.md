# vmdevirt-vtil
This is a project meant for static analysis of vmp3 and has been forked from git.back.engineering although mine has the advantage of actually working. Well, except for the VTIL compiler that is. The vtil compiler was ripped from https://github.com/vtil-project/VTIL-Utils and it is a broken demo that needs fixing. Also, there are multiple vmenters per actual routine and most don't do that much so it would also be nice to stop treating vmenters as functions, instead inserting an unconditional jmp in place of a vmenter to the compiled vtil and then an unconditional jump back so IDA can display it better. Mainly focused on semantic accuracy of the vtil compiler though at the moment (and not crashing which it likes to do)

Update: VTIL is stack overflowing
