## New Machine
## New Machine.Initializing
**On entry:**
- **Do** `New action`

**On** `DONE`:

- **Transition** to [New Machine.Homing](#new-machinehoming)


## New Machine.Homing
**On entry:**
- **Do** `ClearState`

**On** `ERROR`:

- **Transition** to [New Machine.Error](#new-machineerror)

## New Machine.Homing.Homing Reverse
**On** `xstate.after(15s)#New Machine.Homing.Homing Reverse`:

- **Transition** to [New Machine.Error](#new-machineerror)

**On** `DONE`:

- **Transition** to [New Machine.Homing.Homing Forward](#new-machinehominghoming-forward)


## New Machine.Homing.Homing Forward
**On** `xstate.after(15s)#New Machine.Homing.Homing Forward`:

- **Transition** to [New Machine.Error](#new-machineerror)

**On** `DONE` if `shortRange`:

- **Transition** to [New Machine.Homing.Homing Reverse](#new-machinehominghoming-reverse)

**On** `DONE`:

- **Transition** to [New Machine.Menu](#new-machinemenu)



## New Machine.Error
**On** `BUTTON_PRESS`:

- **Transition** to [New Machine.Initializing](#new-machineinitialize)


## New Machine.Menu

