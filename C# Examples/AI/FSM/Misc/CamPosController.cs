using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

/// <summary>
/// Relies on: In editor, children of camPosCollectionParent are in the same order (top - bottom)
///     as CamPosition's values are defined (excluding None). If they're not, input values will not
///     be correctly mapped to camera positions.
/// </summary>
public class CamPosController : MonoBehaviour {

    private enum CamPosition
    {
        None,
        TopDown,
        RearForward,
        LeftForward,
        Selfie
    }
    private CamPosition currentCamPos;

    public GameObject camPosCollectionParent;
    private Component[] allCamPositions;

	void Start ()
    {
        Init();
	}
	
	void Update ()
    {
        UpdateCamPos(GetCamInput());	
	}

    private CamPosition GetCamInput()
    {
        if (Input.GetKeyDown(KeyCode.Keypad1))
            return CamPosition.TopDown;
        else if (Input.GetKeyDown(KeyCode.Keypad2))
            return CamPosition.RearForward;
        else if (Input.GetKeyDown(KeyCode.Keypad3))
            return CamPosition.LeftForward;
        else if (Input.GetKeyDown(KeyCode.Keypad4))
            return CamPosition.Selfie;
        else
            return CamPosition.None;
    }

    private void UpdateCamPos(CamPosition nextPos)
    {
        // Return if no change in pos
        if (nextPos == currentCamPos || nextPos == CamPosition.None)
            return;

        switch (nextPos)
        {
            case CamPosition.TopDown:
                transform.SetParent((Transform)allCamPositions[1], worldPositionStays: false);
                break;
            case CamPosition.RearForward:
                transform.SetParent((Transform)allCamPositions[2], worldPositionStays: false);
                break;
            case CamPosition.LeftForward:
                transform.SetParent((Transform)allCamPositions[3], worldPositionStays: false);
                break;
            case CamPosition.Selfie:
                transform.SetParent((Transform)allCamPositions[4], worldPositionStays: false);
                break;
        }
        currentCamPos = nextPos;
    }

    private void Init()
    {
        Debug.Assert((camPosCollectionParent != null), "CamPosController, Init - camPosCollectionParent is not assigned in the editor");

        allCamPositions = camPosCollectionParent.GetComponentsInChildren<Transform>();

        Debug.Assert((allCamPositions.Length > 0), "CamPosController, Init - No children assigned to camPosCollectionParent. Must have at least 1 child.");

        transform.SetParent((Transform)allCamPositions[1], worldPositionStays: false);
        currentCamPos = CamPosition.RearForward;
    }
}