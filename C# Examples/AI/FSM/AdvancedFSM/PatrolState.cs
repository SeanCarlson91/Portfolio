using UnityEngine;

        npcBrain = brain;
        //Check the distance with player tank
        //When the distance is near, transition to chase state
        if (Vector3.Distance(npc.position, player.position) <= 300.0f)
    {
        mat.color = Color.green;
    }