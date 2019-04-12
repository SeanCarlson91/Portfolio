using UnityEngine;
        {
            if (Vector3.Distance(npc.position, player.position) <= 300f)
                npcBrain.SetTransition(Transition.SawPlayer);
            else
                npcBrain.SetTransition(Transition.LostPlayer);
        }
        {
            npcBrain.Heal();
        }

        destPos = npcBrain.HealingTransform.position;

        if (Vector3.Distance(destPos, npc.position) >= 50f)
        {  
            Quaternion targetRotation = Quaternion.LookRotation(destPos - npc.position);
            npc.rotation = Quaternion.Slerp(npc.rotation, targetRotation, Time.deltaTime * curRotSpeed);

            npc.Translate(Vector3.forward * Time.deltaTime * curSpeed);
        }
    {
        mat.color = Color.white;
    }